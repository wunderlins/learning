#!/usr/bin/env python

# setup environment
# pip install --user ZODB # install into home of user
# pip install --user zodbpickle # install into home of user

# open the zope database
import ZODB, ZODB.FileStorage

#storage = ZODB.FileStorage.FileStorage('mydata.fs')
#db = ZODB.DB(storage)

# Storage shortcuts
db = ZODB.DB('data/mydata.fs') # file database
#db = ZODB.DB(None) # memmory database

connection = db.open()
root = connection.root

# create a btree list of accounts
import BTrees.OOBTree
from account import Account

root.accounts = BTrees.OOBTree.BTree()
root.accounts['account-1'] = Account()

# make changes persistent
import transaction
transaction.commit()
