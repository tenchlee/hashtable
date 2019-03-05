SRCDIR	= src

include ../../os.mk

ifeq ($(debug),1)
	CFLAGS+=-g
	CXXFLAGS+=-g
else
	CFLAGS+=-O2
	CXXFLAGS+=-O2
endif

CFLAGS+=-D__WITH_MURMUR
CXXFLAGS+=-D__WITH_MURMUR

.PHONY: all
all: libhashmap.a

libhashmap.a: $(SRCDIR)/hashtable.h $(SRCDIR)/hashtable.c $(SRCDIR)/murmur.h $(SRCDIR)/murmur.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/hashtable.c $(SRCDIR)/murmur.c
	$(AR) crf $@ hashtable.o murmur.o

test: $(SRCDIR)/main.cpp libhashmap.a
	$(CXX) $^ $(LFLAGS) $(CXXFLAGS) -o $@
	# ./test

clean:
	rm -f *.o
	rm -f test
	rm -f libhashmap.a
