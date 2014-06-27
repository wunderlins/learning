
all: compile sign package test

compile:
	javac upload.java
	javac DirectoryWatcher.java
	javac PostFile.java

package:
	#mv _org org || true
	jar cvf upload.jar upload.class DirectoryWatcher.class PostFile.class \
		httpcomponents-client-4.3.4/lib/*.jar
	
sign:
	jarsigner -storepass $$PASS "upload.jar" "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/commons-codec-1.6.jar "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/httpclient-4.3.4.jar "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/httpmime-4.3.4.jar "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/commons-logging-1.1.3.jar "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/httpclient-cache-4.3.4.jar "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/fluent-hc-4.3.4.jar "upload"
	#jarsigner -storepass $$PASS httpcomponents-client-4.3.4/lib/httpcore-4.3.2.jar "upload"
	
genkey:
	
test:
	mv org _org || true
	killall iceweasel || true
	iceweasel http://localhost/upload.html
	
	
write:
	rm $$HOME/tmp/25.pdf || true
	dd bs=1024000 if=/dev/urandom of=$$HOME/tmp/25.pdf

keytool:
	# -keystore "$1" \
	keytool -genkey -noprompt \
	 -alias "upload" \
	 -dname "CN=Simon Wunderlin, OU=Experimentational, O=Hackers Inc Ltd, L=Basel, ST=BS, C=CH" \
	 -storepass "$$PASS" \
	 -keypass "$$PASS" \
	 -validity 365

