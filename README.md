[![Build Status](https://travis-ci.org/tseemann/dehomopolymerate.svg?branch=master)](https://travis-ci.org/tseemann/dehomopolymerate) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
# dehomopolymerate
Collapse sequence homopolymers to a single character

## Quick Start

```
% cat test/test.fq

@SRR2288572.2 /1
GAATTTCCCC
+
"!!"!"!!!!
@SRR2288572.2 /1
TCGTGTTTTCTTTTTCTTTT
+
"!!"!"!!!!!!!!!!!!!!

% dehomopolymerate test/test.fq

@SRR2288572.2
GATC
+
"!"!
@SRR2288572.2
TCGTGTCTCT
+
"!!"!"!!!!

INPUT  : seqs=2 bp=30 avglen=15
OUTPUT : seqs=2 bp=14 avglen=7
```

## Installation

### Homebrew
```
brew install brewsci/bio/dehomopolymerate   # COMING SOON
```

### From source
`dehomopolymerate` is written in C to the C99 standard 
and only depends on `gcc` and `libz`.

```
git clone https://github.com/tseemann/dehomopolymerate.git
cd dehomopolymerate
make 
make install PREFIX=$HOME/bin
```

## Options

### `-h` (help)

```
% dehomopolymerate -h

SYNOPSIS
  Collapse sequence homopolymers to a single character
USAGE
  dehomopolymerate [options] reads.fast{aq}[.gz] > nohomop.fq
OPTIONS
  -h    Show this help
  -v    Print version and exit
  -q    Quiet mode; not non-error output
  -f    Output FASTA not FASTQ
  -w    Output RAW one line per sequence
URL
  https://github.com/tseemann/dehomopolymerate (Torsten Seemann)
```

### `-v` (version)

Prints the name and version separated by a space in standard Unix fashion.

```
% dehomopolymerate -v
dehomopolymerate 0.1
```

### `-q` (quiet)

Don't print informational messages, only errors.

### `-f` (FASTA output)

```
% dehomopolymerate -f test/test.fq.gz
>SRR2288572.2
GATC
>SRR2288572.2
TCGTGTCTCT
```

### `-w` (raw sequence output, one per line)

```
% dehomopolymerate -w test/test.fq.gz
GATC
TCGTGTCTCT
```

### `-l MINLEN` (minimum length of *output* sequences)

```
% dehomopolymerate -l 6 -f test/test.fq.gz
>SRR2288572.2
TCGTGTCTCT
```

## Issues

File problems here: https://github.com/tseemann/dehomopolymerate/issues

## License

[GPLv3](https://raw.githubusercontent.com/tseemann/dehomopolymerate/master/LICENSE)

## Author

* Torsten Seemann

