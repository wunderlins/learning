#!/usr/bin/env bash

if [[ "$1" == "UploadApplet.java" ]]; then
	javac UploadApplet.java
	jar cvf UploadApplet.jar UploadApplet.class
fi

if [[ "$1" == "FileEventTest.java" ]]; then
		javac FileEventTest.java
		jar cvf FileEventTest.jar FileEventTest.class
fi

if [[ "$1" == "Label3.java" ]]; then
		javac Label3.java
		jar cvf Label3.jar Label3.class
fi

if [[ "$1" == "HelloWorld.java" ]]; then
		javac HelloWorld.java
		jar cvf HelloWorld.jar HelloWorld.class
fi
