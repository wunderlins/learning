
all: compile sign test

compile:
	javac upload.java
	javac DirectoryWatcher.java
	jar cvf upload.jar upload.class DirectoryWatcher.class
	
sign:
	jarsigner -storepass $$PASS "upload.jar" "upload"
	
genkey:
	
test:
	killall iceweasel || true
	iceweasel http://localhost/upload.html
	
write:
	 dd bs=1024000 if=/dev/random of=/home/wus/tmp/22