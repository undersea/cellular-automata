#!/bin/bash

cd data

for x in 3 4;
do
    echo "1/$x training data" >> ../report/output2.log;
    python transform.py $x;
    ../cellular-automata iris_definitions.txt iris_train.data iris_test.data >> ../report/output2.log;
done

