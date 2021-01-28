# libherc - Documentation - argparse

*[back to documentation index](./README.md)*

```c
#include <herc/argparse.h>
```


Want to get started quickly? Check out [the argpase 
cookbook](./cookbook/argparse).

# Exported Functions

The below documentation is reproduced from `argparse.h`, with some
modifications for formatting.

```c
typedef int argparse_callback (struct argparse *self,
                               const struct argparse_option *option);

enum argparse_flag {
    ARGPARSE_STOP_AT_NON_OPTION = 1,
};

enum argparse_option_type {
    /* special */
    ARGPARSE_OPT_END,
    ARGPARSE_OPT_GROUP,
    /* options with no arguments */
    ARGPARSE_OPT_BOOLEAN,
    ARGPARSE_OPT_BIT,
    /* options with arguments (optional or required) */
    ARGPARSE_OPT_INTEGER,
    ARGPARSE_OPT_FLOAT,
    ARGPARSE_OPT_STRING,
};

enum argparse_option_flags {
    OPT_NONEG = 1,              /* disable negation */
};

/**
 *  argparse option
 *
 *  `type`:
 *    holds the type of the option, you must have an ARGPARSE_OPT_END last in your
 *    array.
 *
 *  `short_name`:
 *    the character to use as a short option name, '\0' if none.
 *
 *  `long_name`:
 *    the long option name, without the leading dash, NULL if none.
 *
 *  `value`:
 *    stores pointer to the value to be filled.
 *
 *  `help`:
 *    the short help message associated to what the option does.
 *    Must never be NULL (except for ARGPARSE_OPT_END).
 *
 *  `callback`:
 *    function is called when corresponding argument is parsed.
 *
 *  `data`:
 *    associated data. Callbacks can use it like they want.
 *
 *  `flags`:
 *    option flags.
 */
struct argparse_option {
    enum argparse_option_type type;
    const char short_name;
    const char *long_name;
    void *value;
    const char *help;
    argparse_callback *callback;
    intptr_t data;
    int flags;
};

/**
 * argpparse
 */
struct argparse {
    // user supplied
    const struct argparse_option *options;
    const char *const *usages;
    int flags;
    const char *description;    // a description after usage
    const char *epilog;         // a description at the end
    // internal context
    int argc;
    const char **argv;
    const char **out;
    int cpidx;
    const char *optvalue;       // current option value
};

// built-in callbacks
int argparse_help_cb(struct argparse *self,
                     const struct argparse_option *option);

// built-in option macros
#define OPT_END()        { ARGPARSE_OPT_END, 0, NULL, NULL, 0, NULL, 0, 0 }
#define OPT_BOOLEAN(...) { ARGPARSE_OPT_BOOLEAN, __VA_ARGS__ }
#define OPT_BIT(...)     { ARGPARSE_OPT_BIT, __VA_ARGS__ }
#define OPT_INTEGER(...) { ARGPARSE_OPT_INTEGER, __VA_ARGS__ }
#define OPT_FLOAT(...)   { ARGPARSE_OPT_FLOAT, __VA_ARGS__ }
#define OPT_STRING(...)  { ARGPARSE_OPT_STRING, __VA_ARGS__ }
#define OPT_GROUP(h)     { ARGPARSE_OPT_GROUP, 0, NULL, NULL, h, NULL, 0, 0 }
#define OPT_HELP()       OPT_BOOLEAN('h', "help", NULL,                 \
                                     "show this help message and exit", \
                                     argparse_help_cb, 0, 0)

int argparse_init(struct argparse *self, struct argparse_option *options,
                  const char *const *usages, int flags);
void argparse_describe(struct argparse *self, const char *description,
                       const char *epilog);
int argparse_parse(struct argparse *self, int argc, const char **argv);
void argparse_usage(struct argparse *self);
```

# Upstream Documentation

*The following is reproduced based on the upstream documentation for the
argparse library, with some changes for formatting.*

argparse - A command line arguments parsing library in C (compatible with C++).

## Description

This module is inspired by parse-options.c (git) and python's argparse
module.

Arguments parsing is common task in cli program, but traditional `getopt`
libraries are not easy to use. This library provides high-level arguments
parsing solutions.

The program defines what arguments it requires, and `argparse` will figure
out how to parse those out of `argc` and `argv`, it also automatically
generates help and usage messages and issues errors when users give the
program invalid arguments.

## Features

 - handles both optional and positional arguments
 - produces highly informative usage messages
 - issues errors when given invalid arguments

There are basically three types of options:

 - boolean options
 - options with mandatory argument
 - options with optional argument

There are basically two forms of options:

 - short option consist of one dash (`-`) and one alphanumeric character.
 - long option begin with two dashes (`--`) and some alphanumeric characters.

Short options may be bundled, e.g. `-a -b` can be specified as `-ab`.

Options are case-sensitive.

Options and non-option arguments can clearly be separated using the `--` option.

## Examples

```c
#include "argparse.h"

static const char *const usage[] = {
    "test_argparse [options] [[--] args]",
    "test_argparse [options]",
    NULL,
};

#define PERM_READ  (1<<0)
#define PERM_WRITE (1<<1)
#define PERM_EXEC  (1<<2)

int
main(int argc, const char **argv)
{
    int force = 0;
    int test = 0;
    int num = 0;
    const char *path = NULL;
    int perms = 0;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('f', "force", &force, "force to do"),
        OPT_BOOLEAN('t', "test", &test, "test only"),
        OPT_STRING('p', "path", &path, "path to read"),
        OPT_INTEGER('n', "num", &num, "selected num"),
        OPT_GROUP("Bits options"),
        OPT_BIT(0, "read", &perms, "read perm", NULL, PERM_READ, OPT_NONEG),
        OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE),
        OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
    argc = argparse_parse(&argparse, argc, argv);
    if (force != 0)
        printf("force: %d\n", force);
    if (test != 0)
        printf("test: %d\n", test);
    if (path != NULL)
        printf("path: %s\n", path);
    if (num != 0)
        printf("num: %d\n", num);
    if (argc != 0) {
        printf("argc: %d\n", argc);
        int i;
        for (i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, *(argv + i));
        }
    }
    if (perms) {
        printf("perms: %d\n", perms);
    }
    return 0;
}
```

## FAQ

### Why removing parsed command-line switches/options?

It destroys the original `argv` array, not compatible with other arguments parsing
library.

This is because this library is used for short-lived programs, e.g. cli tools
at beginning. It's very convenient to process remain arguments if we remove
parsed command-line arguments,  e.g. `<comamnd> [-[s]|--switch]... arguments`.

If you want keep original `argc/argv`, you can make a copy, then pass them to
`argparse_parse`, e.g.

```c
int copy_argc          = argc;
const char **copy_argv = argv;
copy_argv  = malloc(copy_argc * sizeof(char *));
for (int i = 0; i < argc; i++) {
	copy_argv[i] = (char *)argv[i];
}
argparse_parse(&argparse, copy_argc, copy_argv);
```

Issues:

- https://github.com/cofyc/argparse/issues/3
- https://github.com/cofyc/argparse/issues/9

### Why using `intptr_t` to hold associated data? Why not `void *`?

I choose `intptr_t` because it's a integer type which also can be used to hold
a pointer value.  Most of the time, we only need a integer to hold
user-provided value, see `OPT_BIT` as example. If you want to provide a pointer
which points to a large amount of data, you can cast it to `intptr_t` and cast
it back to original pointer in callback function.

