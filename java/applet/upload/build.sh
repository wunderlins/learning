#!/usr/bin/env bash

javac UploadApplet.java
jar cvf UploadApplet.jar UploadApplet.class

javac FileEventTest.java
jar cvf FileEventTest.jar FileEventTest.class

