#!/bin/bash

infile=$1

echo $infile

for x in 2 3 4;
do
    echo "$infile 1/$x testing data" >> ../report/report.log;
    ./cellular-automata `python data/transform2.py $infile $x $2` >> report/report.log;
done;


for x in 3 4;
do
    echo "$infile 1/$x training data" >> ../report/report.log;
    ./cellular-automata `python data/transform2.py $infile $x $2 train` >> report/report.log;
done;