import os
import sys





if len(sys.argv) < 2:
    print "expected 1 parameter: directory with text files"
    exit()

pathname = sys.argv[1]
files = os.listdir(pathname)
results = []
for file in files:
    lines = tuple(open(os.path.join(pathname,file), 'r'))
    for i,line in enumerate(lines):
        i += 1
        if len(results) <= i:
            results.append({"riga:":i, "count":len(line) })
        else:
            results[i-1]["count"] += len(line)
print results
