# libherc - Documentation

# Library Documentation

* [khash](./khash.md) - official khash documentation, plus some additional notes.

# Cookbook

The Cookbook aims to have useful, representative examples that can be easily
used as templates.

The [`./cookbook`](./cookbook) directory contains examples of using libherc.
The examples are discussed below.

## Argument Parsing

[`./cookbook/argparse/`](./cookbook/argparse/)

This example is based on the upstream "test" program for
[cofyc/argparse](https://github.com/cofyc/argparse), with slight modifications
to compile against libherc. This program demonstrates how you can use argparse
to parse command-line options in your program.

```
$ make
cc -I/usr/local/include/herc main.c -lherc -L/usr/local/lib
$ ./a.out --help
Usage: test_argparse [options] [[--] args]
   or: test_argparse [options]

A brief description of what the program does and how it works.

    -h, --help            show this help message and exit

Basic options
    -f, --force           force to do
    -t, --test            test only
    -p, --path=<str>      path to read
    -i, --int=<int>       selected integer
    -s, --float=<flt>     selected float

Bits options
    --read                read perm
    --write               write perm
    --exec                exec perm

Additional description of the program after the description of the arguments.
$ ./a.out --path=/path/to/foo.txt --int=73 -s3.4
path: /path/to/foo.txt
int_num: 73
flt_num: 3.4
$ ldd a.out
        linux-vdso.so.1 (0x00007ffc18d86000)
        libherc.so => /usr/local/lib/libherc.so (0x00007f56e5557000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007f56e535b000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007f56e5563000)
```

## Hash Tables

[`./cookbook/hashtable`](./bookbook/hashtable/)

This example demonstrates how to utilize the hash table library provided by
`klib`.


```
$ make
cc -I/usr/local/include/herc main.c -lherc -L/usr/local/lib
$ ./a.out 
h[key2]='val2'
foo not in h
key2 not in h
--- iterate by key ---
h[key3]='val3'
h[key1]='val1'
--- iterate by value ---
h contains value 'val3'
h contains value 'val1'
```
