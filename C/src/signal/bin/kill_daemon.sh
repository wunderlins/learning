#!/usr/bin/env bash

pids=$(ps aux | grep '\. daemon' | grep -v grep | awk -F' ' '{print $2}')
echo "Daemons: "$pids

if [[ ! -z "$pids" ]]; then
	kill $pids
fi
