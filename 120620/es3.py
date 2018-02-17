import os
import sys

def getFileSize(f):
    return os.path.getsize(f)

def getExtremes(val,ex1,ex2):
    res1 = val.split(ex1)
    res2 = res1[1].split(ex2)
    return(res1[0],res2[1])

if len(sys.argv) < 2:
    print "Expected 1 parameter"
    exit()

myarg = sys.argv[1]
ext = getExtremes(myarg,"[","]")
size_sum = 0
for f in os.listdir("."):
    if f.startswith(ext[0]) and f.endswith(ext[1]):
        size_sum += getFileSize(f)
print size_sum
