# node /home/hoang/workspace/stream/Streaming/server/index.js &

# pid=$!
cd /home/hoang/workspace/StreamClient/build/

./StreamClient & 

pid2=$!

echo ${pid}
args=$1
for i in $*; do
if [ "$args" != $i ]
then
    args="$args""\ "$i
    echo "$args"
fi
done

libreoffice --quickstart --show /home/hoang/Document/"$args"

kill ${pid}
kill ${pid2}
