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

# Installation

```
make
sudo make PREFIX=/usr/local install
```

These `make` variables are influential:
* `PREFIX` - libraries will be placed in `PREFIX/lib`, `PREFIX/include`, and
  `PREFIX/bin` as appropriate
* `CC` - C compiler to be used
* `CFLAGS` - C flags to be used
* `CINCLUDE` - C includes

You can run `make info` to see what compiler flags are being used, and where
the library will be installed.

## Troubleshooting

### `error while loading shared libraries: libherc.so: cannot open shared object file: No such file or directory`

Some distributions do not add `/usr/local/lib` to `LD_LIBRARY_PATH` by default.
You should either change `PREFIX` to somewhere your distribution will find it,
or else add `/usr/local/lib` to `LD_LIBRARY_PATH`.

Ubuntu users are advised to add `export
LD_LIBRARY_PATH="/lib:/usr/lib:/usr/local/lib"` to `~/.bashrc` as described
[here](https://askubuntu.com/a/165037).

# Compiling

To compile your program against libherc, you can retrieve the appropriate
compiler flags from `libherc-config` which is generated during `make install`.
For example:

```
gcc $(libherc-config --cflags) main.c $(libherc-config --libs)
```

# Documentation

See [`./doc/README.md`](./doc/README.md).

# Included Libraries

## `cofyc/argparse`

*[cofyc/argparse](https://github.com/cofyc/argparse) / [MIT](https://github.com/cofyc/argparse/blob/master/LICENSE) / [v1.0.2](https://github.com/cofyc/argparse/releases/tag/v1.0.2)*

**Description**: this library provides argument parsing, similar to Python's
argparse.

**Changes**: this library has no changes compared to its upstream release.

## `attractivechaos/klib/khash.h`

*[attractivechaos/klib](https://github.com/attractivechaos/klib/) / MIT / 928581a78413bed4efa956731b35b18a638f20f3*

**Description**: this library provides a hash table implementation.

**Changes**: this library has no changes compared to its upstream release.

## `rxi/vec`

*[rxi/vec](https://github.com/rxi/vec) / [MIT](https://github.com/rxi/vec/blob/v0.2.1/LICENSE) / [v0.2.1](https://github.com/rxi/vec/releases/tag/v0.2.1)*

**Description**: this library provides type-safe dynamically-resizeable vectors
similar to `std::vector` in C++.

**Changes**: this library has no changes compared to its upstream release.


# Directory Structure

* `./src` - source code for the herclib libraries
* `./artifacts` - source tarballs from upstream libraries
* `./doc` - documentation and examples

# Version History

* 0.0.0
  * Add cofyc/argparse v1.0.2
  * Add khash 928581a78413bed4efa956731b35b18a638f20f3
* 0.0.1
  * Add rxi/vec 0.2.1
  * `libherc-config` now has a `--want` flag
    * `libherc-config --want X.Y.Z` will exit 0 if the installed libherc
      version provides version X.Y.Z or better, and 1 otherwise.

# Roadmap

* Add `stb_image.h` and `stb_image_write.h` from
  [nothings/stb](https://github.com/nothings/stb) for reading and writing
  images.
* `<herc/logging.h>` for nice logging macros.
* `<herc/hashtable.h>` for wrappers around khash. This will include some simple
  wrappers around various common khash implementations, e.g. string/string,
  int/string, string/int, string/float, and int/float are the most likely
  candidates. Maybe some for `void*` also. This will be useful for
  inter-operating with other HeRC libraries, since they can all use a common
  type to represent the same data. This is a good candidate for automated code
  generation.
* [`sheredom/subprocess.h`](https://github.com/sheredom/subprocess.h) seems
  like nice wrapper that offers Python `subprocess`-like functionality.
* [DaveGamble/cJSON](https://github.com/DaveGamble/cJSON) a small JSON
  library implemented in C89.
* [benhoyt/inih](https://github.com/benhoyt/inih) an INI parser, similar
  to Python's ConfigParser.
* Some kind of graph library, ideally supporting both directed and undirected
  graphs. We may need to write our own.
* Some kind of linear algebra library. Possibly BLAS plus some wrappers.

## Wishlist

* A nice regular expression library, with some easy to use wrappers around
  common operations.
  * Does string X match regex Y?
  * Replace matches to regex Y in string X with string Z.
  * Where in string X do matches to regex Y occur.
* Unified paramaterization system.
  * Ideally, this would integrate between argparse, config files of some kind,
    and environment variables of some kind, so that any combination of
    them can be used to paramaterize execution of a particular program
    with minimal effort.

# License

See [./LICENSE](./LICENSE). This license only applies to code written or
modifications made here. Many files may be licensed by their respective
upstreams, which is documented above in this README file.
