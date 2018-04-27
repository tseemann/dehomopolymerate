
EXE = dehomopolymerate
PREFIX = /usr/local
TESTDIR = test

CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c99 
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

test:
	./$(EXE) -v
	./$(EXE) -h
	for SEQ in test/test.f* ; do \
	  for OPTS in "-f" "-w" ; do \
  	    echo -ne "Checking $$OPTS $$SEQ\t => " ; \
	    ./$(EXE) $$OPTS $$SEQ 2>&1 | grep -q 'seqs=7 bp=632 avglen=90' || echo "FAIL" && echo "PASS"; \
  	    echo -ne "Checking $$OPTS - < $$SEQ\t => " ; \
	    ./$(EXE) $$OPTS - < $$SEQ 2>&1 | grep -q 'seqs=7 bp=632 avglen=90' || echo "FAIL" && echo "PASS"; \
	  done ; \
	done

