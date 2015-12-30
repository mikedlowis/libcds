#------------------------------------------------------------------------------
# Build Configuration
#------------------------------------------------------------------------------
# Update these variables according to your requirements.

# version
VERSION = 0.0.1

# tools
CC = c99
LD = ${CC}
AR = ar

# flags
INCS = -Itests/         \
       -Isource/        \
       -Isource/buffer  \
       -Isource/exn     \
       -Isource/map     \
       -Isource/murmur3 \
       -Isource/string  \
       -Isource/cmp     \
       -Isource/list    \
       -Isource/mem     \
       -Isource/rbt     \
       -Isource/set     \
       -Isource/vector
CPPFLAGS  = -D_XOPEN_SOURCE=700
CFLAGS   += ${INCS} ${CPPFLAGS}
LDFLAGS  += ${LIBS}
ARFLAGS   = rcs

# commands
COMPILE = @echo CC $@; ${CC} ${CFLAGS} -c -o $@ $<
LINK    = @echo LD $@; ${LD} -o $@ $^ ${LDFLAGS}
ARCHIVE = @echo AR $@; ${AR} ${ARFLAGS} $@ $^
CLEAN   = @rm -f

#------------------------------------------------------------------------------
# Build-Specific Macros
#------------------------------------------------------------------------------
# Library macros and rules
LIBNAME = cds
LIB     = lib${LIBNAME}.a
DEPS    = ${OBJS:.o=.d}
OBJS    = source/vector/vec.o      \
          source/map/map.o         \
          source/string/str.o      \
          source/rbt/rbt.o         \
          source/mem/mem.o         \
          source/murmur3/murmur3.o \
          source/buffer/buf.o      \
          source/list/list.o       \
          source/exn/exn.o         \
          source/set/set.o         \
          source/cmp/cmp.o

# Test binary macros
TEST_BIN  = test${LIBNAME}
TEST_DEPS = ${TEST_OBJS:.o=.d}
TEST_OBJS = tests/main.o      \
            tests/test_list.o \
            tests/test_exn.o  \
            tests/test_str.o  \
            tests/test_set.o  \
            tests/test_vec.o  \
            tests/test_rbt.o  \
            tests/test_map.o  \
            tests/test_buf.o  \
            tests/test.o

# Distribution dir and tarball settings
DISTDIR   = ${LIBNAME}-${VERSION}
DISTTAR   = ${DISTDIR}.tar
DISTGZ    = ${DISTTAR}.gz
DISTFILES = config.mk LICENSE.md Makefile README.md source tests

# load user-specific settings
-include config.mk

#------------------------------------------------------------------------------
# Phony Targets
#------------------------------------------------------------------------------
.PHONY: all options tests dist

all: options ${LIB} ${TEST_BIN} tests

options:
	@echo "Toolchain Configuration:"
	@echo "  CC       = ${CC}"
	@echo "  CFLAGS   = ${CFLAGS}"
	@echo "  LD       = ${LD}"
	@echo "  LDFLAGS  = ${LDFLAGS}"
	@echo "  AR       = ${AR}"
	@echo "  ARFLAGS  = ${ARFLAGS}"

tests: ${TEST_BIN}
	-./${TEST_BIN}

dist: clean
	@echo DIST ${DISTGZ}
	@mkdir -p ${DISTDIR}
	@cp -R ${DISTFILES} ${DISTDIR}
	@tar -cf ${DISTTAR} ${DISTDIR}
	@gzip ${DISTTAR}
	@rm -rf ${DISTDIR}

clean:
	${CLEAN} ${LIB} ${TEST_BIN} ${OBJS} ${TEST_OBJS} ${DEPS} ${TEST_DEPS}
	${CLEAN} ${OBJS:.o=.gcno} ${OBJS:.o=.gcda}
	${CLEAN} ${TEST_OBJS:.o=.gcno} ${TEST_OBJS:.o=.gcda}
	${CLEAN} ${DEPS} ${TEST_DEPS}
	${CLEAN} ${DISTTAR} ${DISTGZ}

#------------------------------------------------------------------------------
# Target-Specific Rules
#------------------------------------------------------------------------------
.c.o:
	${COMPILE}

${LIB}: ${OBJS}
	${ARCHIVE}

${TEST_BIN}: ${TEST_OBJS} ${LIB}
	${LINK}

# load dependency files
-include ${DEPS}
-include ${TEST_DEPS}

