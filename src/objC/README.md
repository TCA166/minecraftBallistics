# Objective C source code

This is the place in the repo where objective C source code is located.

## Why objC?

I decided to use objC because I was curious (foolish) and wanted to try out another C derived objective low level language.
It was a mistake. Do not use objC in your projects.
Here it serves as a nightmarish glue joining D posing as C++ and C wrapped in a class.

## Introduction to objC

If you are reading this you probably don't have much experience with obj C.
And that's for a good reason as it turns out.
From what I have gathered objC originated as an Apple product in the 80s with minimal support and development outside of Apple itself.
This means that from the very beginning the language was exclusively for Apple machines and nowadays even basic things such as a standard haven't been created.
The closest thing you have in objC to a standard library is the Foundation library, originating from Nextstep machines in the 90s (shoutout John Carmack the only guy I have heard of that used these machines).
Other than that you have the GNU project library with some basic features, but no guarantee to function on actual Apple machines.
I have chosen to use this minimal GNU library because I don't really have a choice.

## Objective C

The name fits it fairly well.
It's basically C but with class declarations and method calling utilizing some very weird syntax.
GCC (my compiler of choice) supports objective C outright with no option switching or configuring.
It also provides the objc library which is the GNU library I mentioned beforehand.
You can check out some very basic pure objC code [here](./csvFile.m) where I create a class wrapping some C code.

## Objective C++

Objective C++ is a logical result of gcc and g++ supporting objC files.
It's not really a language as a weird amalgum of C, C++ and objC syntax.
g++ and gcc will compile objective C++ files with no complaining.
I was forced to use this weird franken-language when it turned out that the D support for objC linking required sourcecode changes, changes that would facilitate copying the entire sourcecode with a single line change.
Instead of doing that I decided to simply use objC++.
You can witness the madness that is objC++ [here](./consoleCalculator.mm) where I use an objC class and a C++ class **in the same file**.

## csvFile.h

While you can easily use C (or even C++) in objC, problems arise doing it the other way around.
You cannot use objC objects in C++ and even call the methods itself as functions in C.
GCC by default put the function signatures in the `.text` section of the object file.
This essentially is identical to compiling a function with the `static` keyword.
The solution to this problem was to find out the mangled method names and use `objcopy` to `globalize-symbol` the troublesome functions.
However one more obstacle remained: objC passes two secret arguments to each method.
One is simply equivalent to C++'s this keyword.
It's a pointer to the function instance.
The other is instead the 'command selector'.
I was unable to find details on this peculiar thing, but I was able to determine that when ordinarily calling the method the compiler fills in this argument with the method name followed by a colon for each argument.
You can find a C header file meant to be used as an interface for an objC class [here](./csvFile.h).
