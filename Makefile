
EXE = dehomopolymerate
PREFIX ?= /usr/local
TESTDIR = test

CC ?= gcc
CFLAGS ?= -Wall -Wextra -Ofast -std=c99 
LIBS = -lz -lm

.PHONY: test clean 
.DEFAULT: all

all: $(EXE)

$(EXE): main.c 
	$(CC) $(CFLAGS) -o $(EXE) $^ $(LIBS)

main.c: kseq.h

install: $(EXE)
	install -v -t $(PREFIX)/bin $(EXE)

clean:
	$(RM) *~ *.o $(EXE)

test: $(EXE)
	cd test && ./test.sh


