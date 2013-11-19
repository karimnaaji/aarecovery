#!/bin/bash
# ./run.sh [file] [openit?]
cd media
if [[ -z $1 ]]
then
    files=`ls *.pgm *.ppm`
else
    files=`ls $1.pgm $1.ppm 2> /dev/null`
fi

for f in $files; do
    out=`echo $f | sed 's/\(\.pgm\)/\.png/g;s/\(\.ppm\)/\.png/g'`
    convert $f $out
    if [[ $? == 0 ]]
    then
        echo "Convert: $f -> $out"
    fi
    if [[ $2 -eq 1 ]]
    then
        open $out
    fi
done
cd ..
