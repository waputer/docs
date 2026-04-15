# Waputer Blog #0: Hello Waputer

*Wednesday, April 15, 2026*

Welcome to Waputer. It is a sort of operating system embedded directly in
your browser. If you have found this blog post via some other place, try going
to `waputer.app/blog/0` to see it for yourself. What makes it different from
your typical website? If you are familiar with web development, a quick peek
at the developer console reveals a very unique setup. This blog has far more
in common with programs running on your desktop than a normal website. The short
of it: Waputer allows you to write and run programs that resemble desktop
applications all while remaining inside the browser. It provides a level of
portability and capability that is difficult to achieve any other way. More on
how Waputer works and what makes it unique will be covered in an upcoming
series of blog posts.

The main landing page for Waputer is at `waputer.app`. From there, you can
find the default set of applications. As of writing, there is a link to
WaputerSchool, an application for learning programming, the developer
terminal, a text-driven interface to Waputer, and a preview for Nakö, an IDE
for programming directly on Waputer. There are plans for many additional
applications, and most of the groundwork has been laid for users to develop
and publish their own apps.

The developer terminal is directly accessed by navigating to `waputer.dev`.
There you will find a terminal that is not all that different from the kind
found on the desktop. It has some of the basic tools you would expect,
including `ls` for listing files and `cd` for navigation. Feel free to explore
and tinker. The embedded `help` command can assist in exploring further.


## Goals

I first learned programming using a combination of Visual Studio 6 and Dev-C++
in Windows. It was dead simple to set up a project and run it on any machine I
wanted. Most of the simplicity was due to the fact that everything ran
Windows. It was a useful monoculture. My world, and I think most people's
worlds, are very different now. The desktop is somewhat more varied between
Windows, Mac, and Linux, but that completely leaves out the fact that most
interactions with a computer are on a phone. While there are ways to develop
and run programs on mobile, it quickly gets messy. Waputer, because it is
based in the browser, levels the playing field. Code runs just as well on a
desktop as it does on mobile.

There is the caveat that the phone has a fundamentally different method of
interaction than the desktop. Touch input is different than keyboard and mouse.
The screens are far smaller but have high pixel densities. Waputer does not
save you from these challenges. Programs should be written to account for all
use cases. Existing applications have not yet been adapted to all devices.
Better support is in the works. Even so, programs still have full access to
the display, either as a terminal or GUI, and programs can interact with the
system as expected, such as reading and writing files. My hope is that Waputer
enables users to create and share software as easily as the days of my youth.


## Future Direction

NakoIDE will be brought up to snuff as a full editor that includes all the
bells and whistles one would expect. The end goal would be to enable users to
create full programs using NakoIDE that can be directly published for others
to use. At the click of a button, someone could navigate to a Waputer URL and
run the application, safely contained within the browser. No need for
complicated installers.

WaputerSchool will continue to grow, fleshing out the existing lessons and
adding on more. Future classes will cover data structures and lead into an
introduction to video game design. Waputer itself serves as an ideal
playground for experimenting with programming because of the depth of the
operating system. You are not limited to toy examples that can write to the
screen. You have full access to the system, such as process management,
graphics, and the file system.

The base system itself will continue to evolve and support more features.
Long term storage using a remote, fully encrypted mount is already in the
works. Better usage of WebGL and WebGPU will enable high performance
graphical applications. The ultimate goal for Waputer is to enable users to
develop, publish, and sell applications without ever having to leave the
browser.


### Interoperability

Despite this post emphasizing the browser, it is important to call out that
Waputer and its applications are not intended to be locked to the browser.
There is support, although primitive, for running Waputer using Node.js.
Many of the programs that already exist can run just as well in Linux. Greater
interoperability is important and is planned for Waputer. This goes both ways.
Programs written for Waputer should run outside the browser, and it would be
great for programs written for the desktop to run on Waputer.


## Personal Note

I have spent many years working on various parts of Waputer. It has now
reached a point where it has coalesced into a singular piece of technology. It
is a bit intimidating showing off something you have worked on for so long. I
know some of the decisions are unusual. I have reimplemented many things that
could have been adapted from other projects. Some of it was done out of
necessity. Some of it was done because it simply felt like the right thing to
do. I also know that parts can be done better. There are plenty of places to
improve performance. There are plenty of features that still need to be
completed. I fully intend to continue working on Waputer, fleshing out
everything that is missing and smoothing over the prickly bits.

The part that draws me to programming more than anything else is the
creativity. Solving problems is an inevitable part of programming, but it is
not my main motivation. Like watching a movie, listening to music, or looking
at art, I find it fascinating to see what people make with computers and the
new ways that software gets used. I want Waputer to be that kind of a
platform. Sure, it can make writing and running software easier to do on the
go, moving from device to device; however, I would rather see it used in ways
I never saw coming.

I am predisposed to like open source software. The creativity I like is best
suited in the open, not behind locked doors. Many components of Waputer are
already open source and available on GitHub via `https://github.com/waputer`.
These will always be kept free. Even so, writing and releasing open source
software does not pay bills on its own.

I have a soft spot for teaching and showing others how things work, and that
is the angle I intend to use for Waputer to generate money to support itself.
This is not a large software company. Waputer is completely self-funded. I do
not want to run it like a Silicon Valley startup. I do not want investors. I
simply hope to make it a self-sustaining project that promotes fun and
creativity in software. To those ends, the WaputerSchool app
`waputer.app/school` has an introductory class for learning programming
entirely from scratch. This first class is still being updated with more
chapters and interactive lessons coming shortly. The purchase will give you
access to this lesson and any of its future updates. Also, purchases will
directly support Waputer and its mission to promote learning and creativity in
programming.


## Upcoming Post

Stay tuned to this blog for updates on Waputer. Posts, including updates and
details about Waputer, will be published approximately every two weeks. The
next post will look at the basics of Waputer, including fundamental components
like the file system and process management.


-- Dr. Marc Andrysco
