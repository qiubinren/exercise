#!/bin/sh
while [ 1 -gt 0  ]
do
currenttime=$(date +%H-%M)
currentday=$(date)
if [ $currenttime == '12-00' ]
then
git add /home/qiubinren/daydayup/69gitlearn/readme.txt
git commit -m "autopush-$currentday"
sleep 3600*12;
fi
done
