@class-1.0

# Waputer Blog #1: Waputer as an Operating System

*Friday, May 8, 2026*

Today, we look at what makes Waputer tick. Having some basic understanding of
files and directories, especially those found on Unix-like systems, will
greatly aid in understanding. If you want to skip over some of the gory
details, the Waputer by Examples section goes straight into creating your own
Waputer configurations and sharing them with others.


## Waputer Internals

On the surface, Waputer resembles a typical operating system with the ability
to manipulate files and launch programs, but underneath is a system that allows a
level of portability and sharing that is difficult to find elsewhere. The
system allows you to deploy desktop-like software to a server so that anyone
can instantly run it in the browser. You can think of it as Docker inside the
browser.


### File System

The filesystem underlying Waputer should be familiar to the average power
user. Directories (or folders as they are called in Windows land) may contain
other directories and files. The typical setup contains persisted user files
in `/home`, programs in `/bin`, program data in `/dat`, and so forth. From the
Developer Terminal, you can list files using the familiar `ls` command and
navigate via `cd`. For even more advanced usage, different types of file
systems can be mounted wherever one chooses. All in all, the file system
closely resembles what you might expect on the desktop rather than the
browser. That is exactly the purpose of Waputer. It provides a uniform, well
understood system regardless of where it is run.


### Configurations

The real magic of Waputer occurs inside configurations. When you navigate to
NakoIDE via `waputer.app/nako`, you are telling Waputer to boot up and load
the configuration `nako`. The configuration informs Waputer how to set up the
file system, what files and programs to load and where to put them, and
finally what command to run to get everything going. The configuration is
required for Waputer to do anything at all. Otherwise, it simply sits there
twiddling its thumbs.

Each configuration is available via a unique URL from either `waputer.app` or
`waputer.dev`. Primary applications are published and accessible directly from
the root of the domain, such as `waputer.app/nako` or `waputer.app/school`.
Users can publish their own configurations to a user URL starting with
`@username`. You can visit my own hello world example configuration at
`waputer.dev/@marc/hello`. In this way, Waputer configurations provide one of
the easiest ways to share your work with others. Just publish to the Waputer
server and share the URL to the world.


### Packages

Packages facilitate building configurations by bundling together commonly used
files and programs. For example, many configurations require the standard
command-line programs like `ls` and `cat`, so they are bundled together and
provided on the package `binutils`. These packages mimic packages found in a
package manager in Linux.


### Files

Files from either packages or configurations are used like those on a desktop.
They can be read from and written to by programs. If the file is located in a
persistent location, it will retain changes each time the page is loaded.
Files that come from configurations and packages are a little special. They
are downloaded on demand when the file is first accessed.

Typically, a Waputer file is accessed using a hash, a long jumble of nonsense
letters and numbers, such as
`#2a0a0ec5a33e875be7a7006809fd14021a741c04e2ce1c97b9205422e4557b72` for the
cat utility. When we talk about configurations and packages, they are simply
text files, with their own hash, that specify how to configure the system when
they are loaded. Because hashes are unwieldy to work with, packages and
configuration use friendly names for convenience. The `binutils` package is
translated into the appropriate hash and downloaded that way. You can see it
yourself by downloading `waputer.app/!pkg/binutils`.


### Users

After creating a user account via the sign up page, you are able to upload
files and create your own configurations and packages. Whenever files are
added to the Waputer server, these are publicly available for everyone to
download, so do not host anything you want to keep private.


## Waputer by Example

Before trying out the examples, make sure you have created an account. Be
aware that your account is limited to a few MB of uploads. The ability to get
more storage will be available later, or you can email support now if you have
a convincing use case.


### Hello World

The entirety of the hello world configuration is given below. There are only
two small pieces to it: the `binutils` package listed as the only dependency
and the command `echo Hello world`, using the `echo` command from `binutils`,
to write the text "Hello world" to the screen.

```
{"pkg":["binutils"],"cmd":"/bin/echo Hello world"}
```

Saving the file as `cfg.json` and combined with an account for Waputer, you
can upload and share it with the world using a helper python script `./wapr.py
-c 'dev.@username/hello:cfg.json'`. The helper python script is available via
GitHub at `https://github.com/waputer/scripts`. Once deployed, you can see
your new Waputer configuration in action by navigating to
`waputer.dev@username/hello`. The argument to `wapr.py` is split into three
parts: `dev.` indicates it will be published to the `waputer.dev` domain, the
`@username/hello` part is the name of the package, nested under a username,
and the final `cfg.json` names the configuration file to be used.


### Launching Nako

You are not limited to basic terminal applications with a configuration. Any
package is available, and any command can be used to start Waputer. NakoIDE
itself is found in the package `nako` and can be used to launch the full
application to edit a file of your choosing. The configuration below does
exactly that: it creates a file `/home/file` and launches NakoIDE to edit it.

```
{
	"pkg": ["binutils","nako"],
	"fs": { "home": { "file": "text:Hello world, let's edit" } },
	"cmd": "/bin/nako /home/file"
}
```

If you do not want to create the configuration yourself, navigate to
`waputer.dev/@marc/edit` to see it in action. The program `nako`, very unlike
`echo`, is a fully graphical application. You might see a short flicker of
black when it loads the standard terminal, but it quickly switches into a
graphics mode using WebGL. Details on how the graphics are driven from Waputer
will be a topic for a future post.


## Upcoming Post

Stay tuned to this blog for updates on Waputer. Posts, including updates and
details about Waputer, will be published approximately every two weeks. The
next post will look at the programming languages that power Waputer and its
components such as the file system and process management.


-- Dr. Marc Andrysco
