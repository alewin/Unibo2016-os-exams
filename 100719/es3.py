import os,sys
if os.path.isfile(sys.argv[1]):
    with open(sys.argv[1]) as f:
        lines = f.readlines()
        print lines
        i = 0
        for _ in range(len(lines)):
            if (i+1) < len(lines):
                lines[i],lines[i+1] = lines[i+1],lines[i]
                i+=2
        print lines
else:
    print sys.argv[1] + " is not a file"
