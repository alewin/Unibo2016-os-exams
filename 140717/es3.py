import sys
import os

def write2file(mytext, myfile):
    f = open(myfile,"w+")
    f.write(mytext)

def get_out_string(mydir):
    result = ""
    for dirpath, subdirs, files in os.walk(mydir):
        for f in files:
            result += str(os.path.getsize(f)) + " " + f + "\n"
    return result

if len(sys.argv) < 3:
    print "Expected 3 parameters"
    exit()

work_path = sys.argv[1]
out_file = sys.argv[2]

text = get_out_string(work_path)
write2file(text,out_file)
