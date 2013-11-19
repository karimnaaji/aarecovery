#!/bin/bash
cd media
for f in `ls *.pgm *.ppm`; do
    out=`echo $f | sed 's/\(\.pgm\)/\.png/g;s/\(\.ppm\)/\.png/g'`
    convert $f $out
    if [[ $? == 0 ]]
    then
        echo "Convert : $f -> $out"
    fi
done
cd ..
