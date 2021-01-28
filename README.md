# libherc - C Standard Library for the HeRC Lab

This repository contains a collection of libraries, some of our own making and
some open source. All of them are "vendored", so you don't need any
dependencies outside of this repository. Some libraries may be patched compared
to their "upstream" versions.

This repository is targeted at making it easy to write research code using C by
providing a standard set of routines, data structures, and utilities.

Code in this repository requires the following:

* A C99 compliant C compiler, which supports [statement
  expressions](https://gcc.gnu.org/onlinedocs/gcc/Statement-Exprs.html).
* A POSIX environment with a C standard library.

# Included Libraries

## `cofyc/argparse`

*[cofyc/argparse](https://github.com/cofyc/argparse) / [MIT](https://github.com/cofyc/argparse/blob/master/LICENSE) / [v1.0.2](https://github.com/cofyc/argparse/releases/tag/v1.0.2)*

**Description**: this library provides argument parsing, similar to Python's
argparse.

**Changes**: this library has no changes compared to it's upstream release.

## `attractivechaos/klib/khash.h`

*[attractivechaos/klib](https://github.com/attractivechaos/klib/) / MIT / 928581a78413bed4efa956731b35b18a638f20f3*

**Description**: this library provides a hash table implementation.

**Changes**: this library has no changes compared to it's upstream release.

# Installation

```
make
sudo make PREFIX=/usr/local install
```

These `make` variables are influential:
* `PREFIX` - libraries will be placed in `PREFIX/lib`, `PREFIX/include`, and
  `PREFIX/bin` as appropraite
* `CC` - C compiler to be used
* `CFLAGS` - C flags to be used
* `CINCLUDE` - C includes

You can run `make info` to see what compiler flags are being used, and where
the library will be installed.

# Compiling

To compile your program against libherc, you can retrieve the appropriate
compiler flags from `libherc-config` which is generated during `make install`.
For example:

```
gcc $(libherc-config --cflags) main.c $(libherc-config --libs)
```

# Documentation

See [`./doc/README.md`](./doc/README.md).

# Directory Structure

* `./src` - source code for the herclib libraries
* `./artifacts` - source tarballs from upstream libraries
* `./doc` - documentation and examples

# Version History

* 0.0.0
  * Add cofyc/argparse v1.0.2
  * Add khash 928581a78413bed4efa956731b35b18a638f20f3

# License

See [./LICENSE](./LICENSE). This license only applies to code written or
modifications made here. Many files may be licensed by their respective
upstreams, which is documented above in this README file.
