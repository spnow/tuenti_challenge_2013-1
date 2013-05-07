#!/bin/bash

# Although it is not optimal and it might timeout, this is a simple problem so
# I won't optimize it.
# Python can sum and multiply strings and that's what we need here, so I will
# convert the input to python format, e.g. a2[3c4[de]] to "a"+2*(3*"c"+4*("de))
# and let it do the job.

while read line
do
echo $line | sed "s/\[/(/g" | sed "s/\]/)/g" | sed  "s/\([0-9][0-9]*\)/\1*/g" | sed "s/\([a-z][a-z]*\)/'"'\1'"'/g" | sed "s/\([')]\)\([0-9]\)/\1+\2/g" | sed "s/)'/)+'/g" | awk '{print "import md5;m=md5.new();m.update(" $1 "); print m.hexdigest();"}' | python
done <&0
