#!/usr/bin/env python

import ZODB.config

db = ZODB.config.databaseFromURL('config.xml')
conn = db.open()


