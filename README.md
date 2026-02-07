[![CI](https://github.com/tseemann/dehomopolymerate/workflows/CI/badge.svg)](https://github.com/tseemann/dehomopolymerate/actions)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/tseemann/dehomopolymerate)](https://github.com/tseemann/dehomopolymerate/releases)
[![Bioconda downloads](https://img.shields.io/conda/dn/bioconda/dehomopolymerate)](https://bioconda.github.io/recipes/dehomopolymerate/README.html)
[![License: GPLv3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Language: C99](https://img.shields.io/badge/Language-C99-orangered.svg)](https://en.wikipedia.org/wiki/C99)

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

```
conda install -c bioconda dehomopolymerate
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
  -h      Show this help
  -v      Print version and exit
  -q      Quiet mode; not non-error output
  -f      Output FASTA not FASTQ
  -w      Output RAW one line per sequence
  -l LEN  Discard output sequences shorter then L bp
URL
  https://github.com/tseemann/dehomopolymerate (Torsten Seemann)
```

### `-v` (version)

Prints the name and version separated by a space in standard Unix fashion.

```
% dehomopolymerate -v
dehomopolymerate 0.3
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

File concerns at the
[Issue Tracker](https://github.com/tseemann/dehomopolymerate/issues)

## License

[GPLv3](https://raw.githubusercontent.com/tseemann/dehomopolymerate/master/LICENSE)

## Author

* Torsten Seemann

