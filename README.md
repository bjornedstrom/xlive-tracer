xlive-tracer
============

Fair Warning: This is one of those project I will probably never
finish. But since I spent some effort on it, I thought I'd just
publish the results in case it's useful for someone else. No warranty
etc.

xlive-tracer is a utility for tracing xlive.dll function calls. This
can be useful if your are debugging xlive related problems in the
presence of anti-debugging techniques, such as Securom (or GFWLive
itself, for that matter).

To use it, you are going to need some reverse engineering skills.

- `trace-*` are utility functions for logging C-strings to file.
- `xlive-tracer.*` are selected functions from xlive.dll with tracing.
- `inject-by-proxy.*` is an EXAMPLE entry point (more info below). You will have to replace/modify this to suit your needs.
- `patch.h` is an EXAMPLE file with memory addresses to patch. You will have to replace/modify this to suit your needs.

DLL injection
-------------

Executing code in another process is always a mess. I didn't have
success with common techniques such as CreateRemoteThread or the
Detours library. I also had some problems with Windows Vista "Data
Execution Preventation" which I eventually disabled.

`inject-by-proxy.*` is a stupid trick that worked for me and the game
I was interested in. I simply looked for the smallest dll shipped with
the game, wrote a wrapper around it, and also "trojaned in" my
code. The game happily loaded this into its address space.

TODO
----

xlive does moderately aggressive memory validation even in the calling
process.

Your game will likely also have memory checks.

Background
----------

On Thursday 29 December I purchased a video game which I enjoyed quite
a lot. I played around 1½ hours and was happy with my progress.

The day after, I was going to visit my parents over the weekend and
celebrate New Years eve. Since I usually have some spare time at my
parents, I did what I usually do: I put my save games on my web server
before I caught my train.

Little did I know that those save game files I copied were protected
by "Games for Windows Live", and you cannot simply copy save games
between different computers without some auxiliary profile
information, which I didn't have available at the time.

Thus began the quest to break into my own save games.

<RANT>As a Linux user who mostly boots into Windows to play games, I
am absolutely moritifed how painful it is to do stuff in a Windows
environment. On Linux I'd just read the source. On Windows I have to
deal with copy protection, anti debugging techniques, undocumented
libraries etc etc. Why must the platform be so locked down.</RANT>

License
-------

I don't normally license my stuff under GPL Version 3, but when I do,
it's when I am pissed off at Microsoft.

