# Waputer Blog #2: The Programming Languages of Waputer

*Wednesday, May 27, 2026*

This post looks at the set of languages used by Waputer. The system is split
between a kernel, written in JavaScript, and the userland, supported by two
brand new programming languages. These languages fill what I personally
consider gaps in the developer landscape, and they use a new backend written
specifically to target Waputer and WebAssembly.


## JavaScript

The core component of Waputer, the kernel, is written in JavaScript in order
to support running in the browser. For better or worse, some amount of
JavaScript is necessary to bootstrap WebAssembly. The kernel is responsible
for managing processes, access to files, interprocess communication, memory,
and graphical resources. While JavaScript is necessary to access browser
resources, Waputer quickly transitions to user space, executing programs
written in any language that supports WebAssembly and the system interfaces.


## PL3

PL3 forms the backbone of Waputer. It is the language used for the binary
utilities (ls, cat, etc), common libraries like the Waputer runtime, and many
of the applications such as WaputerSchool. PL3 is designed as a low-level
language that is aimed at fixing many of the warts of C.

Types are always grouped in one place, changing code like `void (*func)(int)`
into `pt:(void(int)) func`. The keywords `var` and `def` are used to declare
variables as in `var i32 = a;`, simplifying many aspects of the language.
Fixed-width types are prioritized over anything else, removing `int` in favor
of `i32` or `i64`. Type casts use a syntax similar to compound literals, i.e.
`u32{-1}`. Importing and exporting code is made much easier with module files,
eliminating the need for `#include` and managing headers. Semicolons are used
after functions so that their syntax matches variable declarations. This also
makes functions more intuitive to nest within one another. There is a whole lot
more that is far beyond what can be covered in a blog post.

I know that some ideas will be controversial. It is not a language for
everyone. I originally drafted the language as an experiment of what a better
version of C would look like to me. After a while, I started using it and
finding joy in writing code using PL3. In the end, it remains a language that
is close to the metal. You are directly responsible for managing all
resources including memory. I believe the level of control makes it ideal for
creating core components and libraries due to its agnostic relationship with
the system. Going between languages with different ways of handling resources
can be difficult and unintuitive, but languages like PL3 or C do not have
those assumptions and are typically easier to integrate with other components.


### User Descriptors

Although not directly a consequence of a new language, PL3 makes use of an
idea of userspace descriptors that make asynchronous I/O easier to work with
at the low level. Rather than exclusively work with file descriptors from a
kernel, programs can create a descriptor that operates completely within the
program. These descriptors act as a way of processing and aggregating events
from kernel descriptors while still supporting the standard type of operations
like poll, read, and write. These features can tie together to create powerful
constructs like the one below, which allocates a pollable descriptor, links
it to an existing file descriptor, and only wakes up the poll when the
callback function processes an input byte of `0xFF`. 

```
var i32 desc = io:alloc();
io:link(desc, fd, io:poll:rd, callback, null);
io:poll1(desc, io:poll:rd, -1);

...

def e:str[u16](i32 desc, u16 got, pt:void arg) callback = {
	if(got & io:poll:rd) {
		var u8 byte;
		io:read(desc, &byte, 1);
		if(byte == 0xFF)
			return io:poll:rd;
	}

	return 0;
};
```

The details and utility of this mechanism are far too involved to be included
here. It is likely going to be an entire blog post of its own in the future.
The use of userspace descriptors is a key ingredient for many tools in
Waputer. Graphic programs make liberal use of them, often reducing the main
function to creating an object, polling its descriptor, and cleaning up once
that poll returns.


### Audit scripts

There are scripts that allow you to compile Waputer going all the way back to
its very first version written in C. These scripts are very fragile and I can
only attest to them running correctly on older packages. Previous versions of
PL3 are riddled with bugs and ill-defined behaviors that are prone to breaking
the build when anything updates. Changes to Clang are the most likely to cause
problems. Even so, I try to maintain the scripts as an audit trail that allows
anyone to verify the compiler from the very beginning and be certain that
there are no sneaky backdoors.


## Dimwit

Dimwit is a higher-level language intended to be easy to learn, easy to use,
and powerful enough to build most applications. It is named after its author
who finds the pace and direction of modern languages too tiring to keep up
with. The language does not aim to be revolutionary or demonstrate any fancy
programming language concept. Sometimes you need a simple language for
building a simple program.

The language features a C-like syntax, compiles to a binary output, and
assists the developer with resource and memory management without fully
abstracting it away. The underlying goal is simplicity. That drives many of
the design decisions. Variables can be declared with or without types.
Technically speaking, non-typed values are an `Any` type. Compound data types
are basic structures and unions. Additional features can be layered on top to
give a more object-oriented feel to compound types, but they remain simple at
their core with methods as a feature added later. Most objects are managed by
reference counting. Rather than provide sophisticated mechanisms, Dimwit opts
to defer to the programmer and provide tools for tracking and debugging memory
problems. Other resources, like files or network connections, already require
more explicit management, and Dimwit treats memory in a similar way. Keep it
simple for simple things and allow more discretion as needed.

Starting with a simple foundation and adding functionality as needed makes
Dimwit ideal for learning to program. A blank file works as a literal starting
point. It is a valid Dimwit program. From there, you can learn how to print
values and create variables without needing to introduce the concept of a
type. Compound types can be introduced without classes. Only later are they
extended to the typical notion of classes and objects.

Dimwit also fulfills the role as the primary application language on Waputer
and perhaps beyond. It is compiled directly to WebAssembly on Waputer, and
attempts to avoid any performance pitfalls that crop up when trying to make a
simple language. It retains a close relationship to low-level languages like
PL3 and C that makes consuming external libraries easy. Over time, I hope that
the ecosystem of Dimwit code enables programmers to quickly throw together
useful apps on Waputer, make use of other developers' code and packages, and
deploy it on Waputer for others to easily run in the browser.


## Machine Ignorant Intermediate Representation

The Machine Ignorant Intermediate Representation (or MIIR) is a library and
intermediate representation for generating output, typically machine code.
Both PL3 and Dimwit leverage MIIR as a backend. The intermediate
representation is intended to be completely agnostic to the final target,
although as the word "ignorant" in the name implies, some assumptions cannot
be cleanly separated. Pointer sizes must be specified up front and are
directly reflected in the IR. By being explicit about pointer sizes, it
greatly simplifies the design and analysis of code. All data is laid out
explicitly in terms of fixed sizes. The main disadvantage is that separate IR
must be generated for different pointer sizes. Overall, MIIR provides an easy
target for the PL3 and Dimwit languages, allowing both languages to benefit
from any improvements made to MIIR.


### Why not LLVM?

Before committing to creating my own intermediate representation, I spent
plenty of quality time with LLVM trying to bend it to my will. In the end, it
was difficult to get working the way I needed, and ultimately not worth the
effort. You can find previous versions of PL3 that target LLVM and the many
hacks it required. Getting variable argument lists to work in a sane manner is
a particularly painful memory. Just try looking at the LLVM code below.

```
// compile with 'clang foo.c -emit-llvm -o- -S -Os'
#include <stdarg.h>
struct T { int a, b, c, d, e; };
int foo(int x, ...) {
	va_list vlist;
	va_start(vlist, x);
	return va_arg(vlist, struct T).e;
}
```

It looks manageable, but notice it does not use the `va_arg` instruction that
LLVM provides. The generated code instead directly manipulates the variable
argument object itself. Even worse, add the flag `-target
aarch64-linux-android` to generate the ARM64 assembly. It is completely
different. So much for being target-independent.

These are the kinds of issues that drove me to create a new intermediate
representation. It also has the side effect of keeping every part of the
toolchain free from the control of big business. Even better, it was far
easier to port the entire system to self-host within Waputer itself. Porting
LLVM to Waputer would have been a Herculean effort. There is plenty of work to
be done on MIIR. It does not generate efficient code. It targets only two
platforms, Linux x86-64 and Waputer. It can do a much better job of analyzing
existing code. It still needs a lot of love.


## Hammer

The tool Hammer is a very simple build system that is used by PL3, Dimwit, and
MIIR. It was originally intended as a small hobby project, but ended up being
really convenient for building virtually any project. It is very similar to
make, opting for a more space-friendly syntax that supports quotes. It is
packaged as a C program embedded in the shell script `hammer.sh`. There is
active work to make Hammer a proper tool that can easily be run on Waputer in
addition to other systems like Linux, Windows, or Mac.


## Upcoming Post

Stay tuned to this blog for updates on Waputer. Posts, including updates and
details about Waputer, will be published approximately every two weeks. The
next post will be a technical deep dive into the binary format used by Waputer
programs. Although it is a valid WebAssembly file, there are a number of
restrictions and creative interpretations to achieve the features available on
Waputer.


-- Dr. Marc Andrysco
