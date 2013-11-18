#!/bin/bash
make && ./aarecovery.out && ./convert.sh 

if [[ $? == 0 ]]
then
    open media/photograph_filtered.png
    open media/photograph_recovered.png
fi
