# Minecraft ballistics

A cool little project that aims to create tools that allow to calculate data regarding minecraft arrow trajectories, while also using as many programming languages as possible.

## Tools

So far only two tools have been produced:

- consoleCalculator - A console utility that acts as a rudimentary minecraft ballistics calculator
- guiCalculator - a gui version of console calculator that also visualizes the trajectory

## Compilation

As of right now the tools utilize four different programming languages (Fortran 90, C, D, C++, objC).
Just run

```sh
make requirements*DNF/APT*
make all
```

To install all necessary requirements on your system and compile everything.
The requirements target comes in two flavors, depending on which package manager you like best.
Feel free to play around with the CFLAGS variable, all the compilers come from GNU so they use the same console frontend.
Also generally a good idea with this project is to stick with GNU compilers as it minimizes chances for name mangling shenanigans or some other compile time nightmares.

## Architecture

### Languages

In order to maximize the amount of languages being used, while also keeping things semi reasonable I imposed upon myself a set of rules:

1. Each language used must be justified in some way
2. All languages must be compiled
3. One use for each language - otherwise why not just use one for everything?
4. No wrapping for the sake of wrapping - otherwise I could just wrap functions in functions until the end of time

So as of right now five languages are used, each for a different purpose:

1. Fortran - for math
2. C - for the C csv library
3. Objective C - for the console utility frontend
4. D - for the OOP Fortran wrapper (Did you know that D has a crazy level of linkage support?)
5. C++ - for the GUI app

### Dependency Tree
