#!/usr/bin/env bash

while read p; do
	echo $p | sed -e 's/^const char \*//; s/ //g;'
done < "files.h" > var/files.sh
. var/files.sh

make kill
make all
make test
echo ""

#make pid | tail -n1 > $PID_FILE

pid=$(cat $signals_pid)
echo "PID: $pid";

./send TERM $pid
