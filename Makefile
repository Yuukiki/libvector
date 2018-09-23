LIBNAME := libvector

CC ?= gcc
AR ?= ar
RANLIB ?= ranlib
CFLAGS += -Werror -Wall -Wextra -g
CPPFLAGS += -Iinclude
LDFLAGS += -L. -lvector -Wl,-rpath,$(PWD)

all: shared_lib

shared_lib:
	$(CC) -shared -fPIC -o $(LIBNAME).so vector.c $(CFLAGS) $(CPPFLAGS)

static_lib:
	$(CC) -c vector.c $(CFLAGS) $(CPPFLAGS)
	$(AR) -rcu $(LIBNAME).a vector.o
	$(RANLIB) $(LIBNAME).a

test: shared_lib
	$(CC) -o test test.c $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	@rm -rf *.o *.so *.a test
