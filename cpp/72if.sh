#!/bin/sh
for i in $( seq 11 )
do
if [ $i -eq 11 ]
then
echo " i = 11 "
else
echo " i < 11 "
fi
done
