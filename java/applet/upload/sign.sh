#!/usr/bin/env bash

valid=36500
ass="ter39gwi"

#keytool -genkey -alias "$1" -validity $valid

# Enter keystore password:  
# What is your first and last name?
#   [Unknown]:  Simon Wunderlin
# What is the name of your organizational unit?
#   [Unknown]:  Experimentational
# What is the name of your organization?
#   [Unknown]:  Hackers Inc Ltd
# What is the name of your City or Locality?
#   [Unknown]:  Basel
# What is the name of your State or Province?
#   [Unknown]:  BS
# What is the two-letter country code for this unit?
#   [Unknown]:  CH
# Is CN=Simon Wunderlin, OU=Experimentational, O=Hackers Inc Ltd, L=Basel, ST=BS, C=CH correct?
#   [no]:  yes


# -keystore "$1" \
#keytool -genkey -noprompt \
# -alias "$1" \
# -dname "CN=Simon Wunderlin, OU=Experimentational, O=Hackers Inc Ltd, L=Basel, ST=BS, C=CH" \
# -storepass "$ass" \
# -keypass "$ass" \
# -validity $valid

jarsigner "$1.jar" "$1"

