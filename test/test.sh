#!/usr/bin/env bash

EXE=../dehomopolymerate

ANSWER1="seqs=7 bp=632 avglen=90"
ANSWER2="seqs=6 bp=628 avglen=104"

$EXE -v
$EXE -h
for SEQ in test.{fa,fq,fa.gz,fq.gz}; do 
  for OPTS in "-f" "-w" "-f -w"; do
    echo -ne "Checking $OPTS $SEQ\t=>\t"
    $EXE $OPTS $SEQ 2>&1 | grep -q -F "$ANSWER" || echo "FAIL" && echo "PASS"
    echo -ne "Checking $OPTS - < $SEQ\t=>\t"
    $EXE $OPTS - < $SEQ 2>&1 | grep -q -F "$ANSWER" || echo "FAIL" && echo "PASS"
  done
  OPTS="-l 5"
  echo -ne "Checking $OPTS - < $SEQ\t=>\t"
  $EXE $OPTS $SEQ 2>&1 | grep -q -F "$ANSWER2" || echo "FAIL" && echo "PASS"
done

