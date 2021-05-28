# Data Structures and Algorithms Code Examples from Video Lectures

Most all of the code examples I use in the video lectures for this class can
be found in this directory.  A simple `Makefile` has been included that will
build all target executables in the directory.  I resisted the urge to make
the `Makefile` build more complicated so that you should be able to relatively
easily understand the `Makefile` and how it works.  Most of the files are
built from a single source file.  A few of the example source files have
compiler warnings in the code that were in there on purpose, to illustrate
some point.  So some of the files are compiled without treating warnings as
a compilation error, so that the target executable can be made even with
warnings on the compilation.

Despite what I said in one of my videos, this `Makefile` will build on
Windows systems fine.  It appears that by default the gcc/g++ compiler will
add on the needed `.exe` extension to the target executable when it links
it together.  The only modification needed is to add `*.exe` for the
`make clean` target so that the executables are cleaned up on Windows.

## Usage

```
# to build all examples
$ make all

# to build a specific example
$ make w01-1

# to clean all files so can perform a clean build
$ make clean
```

There are no targets to run an example file after building it. If you would
like to have a run target in your build, so that you can build and run and
see the output in the Atom Editor IDE, you can add something like the
following into the Makefile

```Makefile
run: w01-1
  ./w01-1
```

This target will first build the w01-1 target executable if it is out of
date, and will then run the resulting executable.  Don't forget that you need
an actual `TAB` character on the line in front of the command that the
target runs (e.g. you need a hard tab characters before the `./w01-1` in
this file).

## Makefile Details

We kept the `Makefile` relatively simple, but to avoid some repetition we did
make use of some `Makefile` features.

First of all the `define` is very similar to `#define` in C/C++.  The bit
of code in the `Makefile` `define` will simply replace all instances of the
`$(compile-single)` in the file below that.

But the compilation command we used looks like this:

```Makefile
define compile-single
  g++ -Wall -Werror -pedantic $< -o $@
endef
```

You should be familiar with invoking the `g++` compiler.  We use the compiler
flags `-Wall -Werror -pedantic` basically to adhere to strict C coding
standards (pedantic) and to report all errors and warnings and to treat all
warnings like they are compiler errors.  These flags force us to be more
careful in the code we write, to remove and understand warnings, and to not
rely on non-standard compiler extensions or syntax.

But you may not know the meaning of the `$<` and `$@` on this compilation
command.  These are what are known as `Makefile`
[automatic variables](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html).
These are variables, like variables in a programming language, that take on
specific values within the context of a make target.  In particular
`$<` will be replaced by the name of the first prerequisite in the
target, and `$@` will be replaced by the name of the target.  So for
example, a target like this:

```Makefile
w01-1: w01-1-UserDefinedFunctions.cpp
  g++ -Wall -Werror -pedantic $< -o $@
```

Is the same as if we had written it explicitly like this:

```Makefile
w01-1: w01-1-UserDefinedFunctions.cpp
  g++ -Wall -Werror -pedantic w01-1-UserDefinedFunctions.cpp -o w01-1
```

But of course the automatic variables are much more useful because we can
reuse the version with the automatic variables for most all of the update
commands without having to rewrite anything to refer to the source file
and the target executable name.
