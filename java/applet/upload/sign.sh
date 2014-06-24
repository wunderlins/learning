#!/usr/bin/env bash

valid=36500

keytool -genkey -alias "$1" -validity $valid

jarsigner "$1.jar" "$1"

