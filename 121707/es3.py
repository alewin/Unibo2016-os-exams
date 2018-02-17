import os
import sys

if len(sys.argv) < 2:
    exit()

def tree (pathname):
    for root, dirs, files in os.walk(mydir):
        files.sort()
        for f in files:
            print os.path.abspath(os.path.join(root,f))



mydir = sys.argv[1]
tree2(mydir)
