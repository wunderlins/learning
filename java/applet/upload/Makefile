
all: compile sign test

compile:
	javac upload.java
	jar cvf upload.jar upload.class
	
sign:
	jarsigner "upload.jar" "upload"
	
genkey:
	
test:
	killall iceweasel || true
	iceweasel http://localhost/upload.html