import os
import sys

if len(sys.argv) < 4:
    print "Expected 3 parameters letter directory frequency"
    exit()

def maxfreq(mychar, mydir, myfreq):
    top = []
    for dirpath, dirnames, filenames in os.walk(mydir):
        for i,f in enumerate(filenames):
            top.append( [f,f.count(mychar)] )
    top.sort(key=lambda x: x[1],reverse=True)
    return top




print maxfreq(sys.argv[1],sys.argv[2],sys.argv[3])
