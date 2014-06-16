#!/usr/bin/env bash

PIDS=$(ps aux | grep signal | grep -v grep | awk -F' ' '{print $2}')

if [[ -n "$PIDS" ]]; then
	echo "Killing processes: "$PIDS;
	kill -9 $PIDS
fi

