import os
import sys

if len(sys.argv) < 3:
    print "Expected 2 parameters dir1 dir2"
    exit()

if os.path.isdir(sys.argv[1]) == False & os.path.isdir(sys.argv[2]) == False:
    print "parameters must be existing folder"
    exit()

dir1 = os.path.abspath(sys.argv[1])
dir2 = os.path.abspath(sys.argv[2])

for root,dirs,files in os.walk(dir1):
    for f in files:
        src = os.path.join(dir1, f)
        dst = os.path.join(dir2, f)
        print src
        print dst
        os.symlink(src,dst)
        #os.path.join(root, f)
        #os.path.isfile(file_path)
