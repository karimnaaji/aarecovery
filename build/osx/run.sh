#!/bin/bash
make && ./aarecovery.out $1 && ./convert.sh $1

if [[ $? == 0 ]]
then
    filtered=$1"_filtered"
    recovered=$1"_recovered"
    ./convert.sh $filtered 1
    ./convert.sh $recovered 1
fi
