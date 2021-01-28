# Copyright 2021 Jason Bakos, Charles Daniels
#
# This file is distributed as part of the libherc library distribution, and
# is released under a BSD 3-clause style license.

SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

CC?=gcc
CFLAGS?=-Wall -Wextra -pedantic -Wmisleading-indentation -Werror -std=gnu11 -g -Og
CINCLUDE?=
LD?=ld
PREFIX?=/usr/local
INCLUDE_DIR?=$(PREFIX)/include
LIB_DIR=$(PREFIX)/lib
BIN_DIR=$(PREFIX)/bin

LIBHERC_VERSION=0.0.0

sources = $(wildcard src/*.c)
headers = $(wildcard src/*.h)
objects = $(patsubst src/%.c,src/%.o,$(sources))

all: src/libherc.so src/libherc.a
.PHONY: all

version:
	@echo "libherc version $(LIBHERC_VERSION)"
.PHONY: version

info:
	@echo "CC . . . . . . $(CC)"
	@echo "CFLAGS . . . . $(CFLAGS)"
	@echo "CINCLUDE . . . $(CINCLUDE)"
	@echo "LD . . . . . . $(LD)"
	@echo "PREFIX . . . . $(PREFIX)"
	@echo "INCLUDE_DIR  . $(INCLUDE_DIR)"
	@echo "LIB_DIR  . . . $(LIB_DIR)"
	@echo "BIN_DIR  . . . $(BIN_DIR)"
.PHONY: info

install:
	mkdir -p "$(BIN_DIR)"
	mkdir -p "$(LIB_DIR)/herc"
	mkdir -p "$(INCLUDE_DIR)/herc"
	echo '#!/bin/sh' > "$(BIN_DIR)/libherc-config"
	echo 'VERSION="$(LIBHERC_VERSION)"' >> "$(BIN_DIR)/libherc-config"
	echo 'USAGE="libherc-config [--cflags] [--libs] [--version] [--help]"' >> "$(BIN_DIR)/libherc-config"
	echo 'if [ $$# -lt 1 ] ; then echo "$$USAGE" ; exit 1 ; fi' >> "$(BIN_DIR)/libherc-config"
	echo 'while true ; do' >> "$(BIN_DIR)/libherc-config"
	echo 'if [ $$# -lt 1 ] ; then exit 0' >> "$(BIN_DIR)/libherc-config"
	echo 'elif [ "$$1" = "--help" ] ; then echo "$$USAGE" ; shift'  >> "$(BIN_DIR)/libherc-config"
	echo 'elif [ "$$1" = "--cflags" ] ; then echo "-I$(INCLUDE_DIR)/herc" ; shift' >> "$(BIN_DIR)/libherc-config"
	echo 'elif [ "$$1" = "--libs" ] ; then echo "-lherc -L$(LIB_DIR)" ; shift' >> "$(BIN_DIR)/libherc-config"
	echo 'elif [ "$$1" = "--version" ] ; then echo "$$VERSION" ; shift' >> "$(BIN_DIR)/libherc-config"
	echo 'else echo "unrecognized option $$1" ; echo "$$USAGE" ; exit 1 ; fi' >> "$(BIN_DIR)/libherc-config"
	echo 'done' >> "$(BIN_DIR)/libherc-config"
	chmod +x "$(BIN_DIR)/libherc-config"
	cp ./src/*.so "$(LIB_DIR)"
	cp ./src/*.a "$(LIB_DIR)"
	cp ./src/*.h "$(INCLUDE_DIR)/herc/"
.PHONY: install

src/libherc.so: $(objects)
	$(LD) -shared $^ -o $@

src/libherc.a: $(objects)
	ar cr $@ $^

src/%.o: src/%.c $(headers)
	$(CC) -fPIC $(CFLAGS) -c $< -o $@ $(CINCLUDE)

clean:
	rm -f $(objects) src/libherc.so src/libherc.a
.PHONY: clean
