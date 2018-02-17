import sys
import os

def getFreq(mydir):
    freq = [0]
    for root, dirs, files in os.walk(mydir):
        for f in files:
            if(freq[0]):
                for i in freq[0]:
                    print 0
            else:
                freq.append({len(f): 0})

    return freq


if len(sys.argv) < 2:
    print "Expected 1 parameter: directory"
    exit()

mydir = sys.argv[1]
fie = getFreq(mydir)
print fie
