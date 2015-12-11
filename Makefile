#------------------------------------------------------------------------------
# Build Configuration
#------------------------------------------------------------------------------
# Update these variables according to your requirements.

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

#------------------------------------------------------------------------------
# Build Targets and Rules
#------------------------------------------------------------------------------
SRCS = source/vector/vec.c      \
       source/map/map.c         \
       source/string/str.c      \
       source/rbt/rbt.c         \
       source/mem/mem.c         \
       source/murmur3/murmur3.c \
       source/buffer/buf.c      \
       source/list/list.c       \
       source/exn/exn.c         \
       source/set/set.c         \
       source/cmp/cmp.c
OBJS = ${SRCS:.c=.o}

TEST_SRCS = tests/main.c      \
            tests/test_list.c \
            tests/test_exn.c  \
            tests/test_str.c  \
            tests/test_mem.c  \
            tests/test_set.c  \
            tests/test_vec.c  \
            tests/test_rbt.c  \
            tests/test_map.c  \
            tests/test_buf.c  \
            tests/test.c
TEST_OBJS = ${TEST_SRCS:.c=.o}

all: options libcds.a testcds

options:
	@echo "Toolchain Configuration:"
	@echo "  CC       = ${CC}"
	@echo "  CFLAGS   = ${CFLAGS}"
	@echo "  LD       = ${LD}"
	@echo "  LDFLAGS  = ${LDFLAGS}"
	@echo "  AR       = ${AR}"
	@echo "  ARFLAGS  = ${ARFLAGS}"

libcds.a: ${OBJS}
	@echo AR $@
	@${AR} ${ARFLAGS} $@ ${OBJS}

testcds: ${TEST_OBJS} libcds.a
	@echo LD $@
	@${LD} -o $@ ${TEST_OBJS} libcds.a ${LDFLAGS}
	-./$@

.c.o:
	@echo CC $<
	@${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f libcds.a testcds ${OBJS} ${TEST_OBJS}

.PHONY: all options

