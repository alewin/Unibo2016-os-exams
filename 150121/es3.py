#!/usr/bin/python

import sys
import os
import hashlib

def Getfilesmd5(path):
    result = []
    for dirpath, subdirs, files in os.walk(path):
        for f in files:
            md5 = hashlib.md5(open(os.path.join(dirpath, f),'rb').read()).hexdigest()
            result.append(md5)
    return result

def summd5(mylist):
    print mylist
    for x in mylist:
        print x

files_in_md5 = []
if len(sys.argv) < 2:
    files_in_md5 = Getfilesmd5(os.path.dirname(os.path.abspath(__file__)))
else:
    files_in_md5 = Getfilesmd5(sys.argv[1])

summd5(files_in_md5)
