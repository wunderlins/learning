#!/usr/bin/env bash

rm -R doc/*
doxygen doxygen.cfg
mv html latex doc
