
all: compile sign test

compile:
	javac upload.java
	javac DirectoryWatcher.java
	#javac PostFile.java
	jar cvf upload.jar upload.class DirectoryWatcher.class #PostFile.class
	
sign:
	jarsigner -storepass $$PASS "upload.jar" "upload"
	
genkey:
	
test:
	killall iceweasel || true
	iceweasel http://localhost/upload.html
	
write:
	rm $$HOME/tmp/25
	dd bs=1024000 if=/dev/urandom of=$$HOME/tmp/25

keytool:
	# -keystore "$1" \
	keytool -genkey -noprompt \
	 -alias "upload" \
	 -dname "CN=Simon Wunderlin, OU=Experimentational, O=Hackers Inc Ltd, L=Basel, ST=BS, C=CH" \
	 -storepass "$$PASS" \
	 -keypass "$$PASS" \
	 -validity 365

