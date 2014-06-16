#!/usr/bin/env bash

ps aux | grep signal | grep -v grep | awk -F' ' '{print $2}'
