#!/bin/sh
function start
{
touch start.sh
chmod 744 start.sh
echo "test" >start.sh
cat /dev/null > start.sh
echo "#!/bin/sh" >>start.sh
echo "sleep 10" >>start.sh
./start.sh &
wait
echo "start excurate ending..."
}
i=1
case "$i"
in
0)echo 0;;
1)start;;
*)echo "default...";;
esac
