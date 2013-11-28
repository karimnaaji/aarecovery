#!/bin/bash
make && ./aarecovery.out -o $1 

if [ $? == 0 ] && [ $2 -eq 1 ]
then
    filtered=$1"_filtered"
    recovered=$1"_recovered"
    ./convert.sh $1 1
    ./convert.sh $filtered 1
    ./convert.sh $recovered 1
    ./convert.sh sobel 1
fi
