# C Data Structures Lib

    Created By: Michael D. Lowis & A. Bellenir
    Email:      mike@mdlowis.com; libcds@bellenir.com

## About This Project

This library is meant to be a collection of common data structures, implemented
in C, that can be used in any C or C++ program. The goal is to implement many
of the same data structures that the C++ STL provides, in pure C.

## License

Unless explicitly stated otherwise, all code and documentation contained within
this repository is released under the BSD 2-Clause license. The text for this
license can be found in the LICENSE.md file.

## Build Instructions

### Requirements For Building

A POSIX-compliant implementation of Make and a C99 compatible compiler
(appearing as the command "c99" in the path) are all that is required to build
this project.

### Configuring the Build

The build is configured to build using c99 with POSIX-compliant tools and
settings by default. These settings can be overridden using the config.mk file
in the root of the project. This file contains a number of commented out macros
which can be uncommented and adjusted to provide a variety of useful features
for development.

### Building

Simply execute make from the root to run all tests and build the library:

    make

