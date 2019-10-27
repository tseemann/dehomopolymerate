#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <getopt.h>

#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

#define EXENAME "dehomopolymerate"
#define GITHUB_URL "https://github.com/tseemann/dehomopolymerate"
#define AUTHOR "Torsten Seemann"
#define VERSION "0.4.0"

// warning: implicit declaration of function 'fileno' [-Wimplicit-function-declaration]
int fileno(FILE *stream);

//------------------------------------------------------------------------
void show_help(int retcode)
{
  FILE* out = (retcode == EXIT_SUCCESS ? stdout : stderr);
  fprintf(out, "SYNOPSIS\n  Collapse sequence homopolymers to a single character\n");
  fprintf(out, "USAGE\n  %s [options] reads.fast{aq}[.gz] > nohomop.fq\n", EXENAME);
  fprintf(out, "OPTIONS\n");
  fprintf(out, "  -h      Show this help\n");
  fprintf(out, "  -v      Print version and exit\n");
  fprintf(out, "  -q      Quiet mode; not non-error output\n");
  fprintf(out, "  -f      Output FASTA not FASTQ\n");
  fprintf(out, "  -w      Output RAW one line per sequence\n");
  fprintf(out, "  -l LEN  Discard output sequences shorter then L bp\n");
  fprintf(out, "URL\n  %s (%s)\n", GITHUB_URL, AUTHOR);
  exit(retcode);
}

//------------------------------------------------------------------------
int kseq_remove_homopolymers(kseq_t* r) {
  int fq = r->qual.l; 
  char s2[r->seq.l+1];
  char q2[r->seq.l+1];
  char* s = r->seq.s;
  char* q = r->qual.s;
  size_t j=1, i=1;
  s2[0] = s[0];
  if (fq) q2[0] = q[0];
  for (; i < r->seq.l; i++) {
    if (s[i] != s[i-1]) {
      s2[j] = s[i];
      if (fq) q2[j] = q[i];
      j++;
    }
  }
  s2[j] = '\0';
  if (fq) q2[j] = '\0';
  //printf("i=%u j=%u s2=%s q2=%s\n", i, j, s2, q2);
  strcpy(s, s2);
  if (fq) strcpy(q, q2);
  r->seq.l = j;
  if (fq) r->qual.l = j;
  return j;
}
 
//------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // parse command line parameters
  int opt, quiet=0, fasta=0, raw=0, minlen=0;
  while ((opt = getopt(argc, argv, "hvql:fw")) != -1) {
    switch (opt) {
      case 'h': show_help(EXIT_SUCCESS); break;
      case 'v': printf("%s %s\n", EXENAME, VERSION); exit(EXIT_SUCCESS);
      case 'q': quiet=1; break;
      case 'f': fasta=1; break;
      case 'w': raw=1; break;
      case 'l': minlen=atoi(optarg); break;
      default : show_help(EXIT_FAILURE);
    }
  } 

  // say hello
  if (!quiet) {
    //fprintf(stderr, "RUNNING: %s %s from %s\n", EXENAME, VERSION, GITHUB_URL);
    //fprintf(stderr, "minlen=%d\n", minlen);
  }
  // open stdin or the file on commandline
  FILE* input = NULL;
  if (optind >= argc) {
    // no file specified so check if stdin is a pipe
    if (isatty(fileno(stdin))) {
      show_help(EXIT_FAILURE);
    }
    else {
      input = stdin;
    }
  }
  else {
    // opening a filename
    const char* seqfn = argv[optind];
    // "-" is the special filename for stdin
    input = strcmp(seqfn, "-") ? fopen(seqfn, "r") : stdin;
    if (! input) {
      fprintf(stderr, "ERROR: Could not open '%s'\n", seqfn);
      exit(EXIT_FAILURE);
    }
  }

  // open filehandle with zlib
  gzFile fp = gzdopen(fileno(input), "r"); 
  if (! fp) {
    fprintf(stderr, "ERROR: Could not gzopen input\n");
    exit(EXIT_FAILURE);  
  }

  // setup loop  
  long l, N=0, L=0, L2=0, N2=0;
  kseq_t* kseq = kseq_init(fp);

  // loop over sequences
  while ((l = kseq_read(kseq)) >= 0) {    
    // keep input stats
    N++;
    L += l;
    
    // tranform in place - will be shorter so no alloc() needed
    int len = kseq_remove_homopolymers(kseq);
    // fprintf(stderr, "l=%ld l'=%d minlen=%d\n", l, len, minlen);
    
    // skip over short sequences as per -l parameter
    if (len < minlen) continue;
    
    // print to stdout
    if (raw) {
      puts(kseq->seq.s);
    }
    else if (fasta || kseq->qual.l <= 0) {   // want fasta, or input was fasta
      printf(">%s\n%s\n", kseq->name.s, kseq->seq.s);
    }
    else {
      // not printing comment here
      printf("@%s\n%s\n+\n%s\n", kseq->name.s, kseq->seq.s, kseq->qual.s);
    }
    // keep output stats
    L2 += len;
    N2++;
  }
  
  // cleanup
  kseq_destroy(kseq); 
  gzclose(fp); 

  // reveal status
  if (!quiet) {
    fprintf(stderr, "INPUT  : seqs=%ld bp=%ld avglen=%ld\n", N, L, L/N);
    fprintf(stderr, "OUTPUT : seqs=%ld bp=%ld avglen=%ld\n", N2, L2, L2/N2);
  }

  return 0;
}

//------------------------------------------------------------------------
