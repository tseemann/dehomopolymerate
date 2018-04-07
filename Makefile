
EXE = dehomopolymerate
PREFIX = /usr/local
TESTDIR = test

CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 
LIBS = -lz -lm

.PHONY: check clean
.DEFAULT: all

all: $(EXE)

$(EXE): main.c 
	$(CC) $(CFLAGS) -o $(EXE) $^ $(LIBS)

main.c: kseq.h

install: $(EXE)
	install -v -t $(PREFIX)/bin $(EXE)

clean:
	$(RM) *~ *.o $(EXE)

test:
	./$(EXE) -v
	./$(EXE) -h
	./$(EXE) < $(TESTDIR)/test.fq.gz
	./$(EXE) - < $(TESTDIR)/test.fq.gz
	./$(EXE) $(TESTDIR)/test.fq.gz
	./$(EXE) -f $(TESTDIR)/test.fq.gz
	./$(EXE) -w $(TESTDIR)/test.fq.gz	

