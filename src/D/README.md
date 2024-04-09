# D source code

Part of this project was written in D.
The object oriented math wrapper part to be exact.

## Why D?

Because D has a pretty good amount of linkage support.
It can easily link with C, C++ and objective C which is more than most languages can claim.
This support includes methods, inheritance and even exceptions!
Also D is a very nice language that very clearly improves on plenty of issues with C++.

## Why is there a link script?

Well D doesn't support multi inheritance.
This lack of support seems to extend to the C++ compatibility layer where D won't create function signatures for different constructors.
C++ expects different versions of multi inheritance to have their own constructors.
So for example in my build environment plainly inheriting from a class(or creating a new instance of a class) calls the '...C1...' function.
While for other inheritance it might call '...C2...', '...C3...' and so on.
This is an issue and leads to very weird compile time errors.
So we have a link script to rename C2 and C3 calls.
If you ever want to use this D wrapper in your own project, and want to do say 4 time inheritance then you will need to modify this linkage script.
