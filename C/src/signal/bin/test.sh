#!/usr/bin/env bash

PID_FILE="var/signal.pid"

make kill
make all
make test
echo ""
make pid | tail -n1 > $PID_FILE

pid=$(cat $PID_FILE)
echo "signal: $pid";

./send HUP $pid