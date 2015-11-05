#!/bin/sh
while [ 1 -gt 0  ]
do
currenttime=$(date +%H-%M)
currentday=$(date)
if [ $currenttime == '12-00' ]
then
cd /home/qiubinren/exercese
git add *
git commit -m "autopush-$currentday"
git push -m origin master
fi
done
