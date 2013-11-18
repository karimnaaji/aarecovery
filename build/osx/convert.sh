#!/bin/bash
cd media
for f in `ls *.pgm`; do
    out=`echo $f | sed 's/\.pgm/\.png/'`
    convert $f $out
    if [[ $? == 0 ]]
    then
        echo "Convert : $f -> $out"
    fi
done
cd ..
