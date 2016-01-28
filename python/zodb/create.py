#!/usr/bin/env python

# setup environment
# pip install --user ZODB # install into home of user
# pip install --user zodbpickle # install into home of user

# open the zope database
import ZODB, ZODB.FileStorage, ZODB.config, BTrees.OOBTree, transaction
import pprint

"""
#storage = ZODB.FileStorage.FileStorage('mydata.fs')
#db = ZODB.DB(storage)

# Storage shortcuts
db = ZODB.DB('data/mydata.fs') # file database
#db = ZODB.DB(None) # memmory database
connection = db.open()
"""

# using a config file to open the database
db = ZODB.config.databaseFromURL('config.xml')
connection = db.open()

# get the root node
root = connection.root

# create a btree list of accounts
from account import Account

root.accounts = BTrees.OOBTree.BTree()
root.accounts['account-4'] = Account()

# make changes persistent
transaction.commit()

# show root
for n in root.accounts:
	pprint.pprint(root.accounts[n])
