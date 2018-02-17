import sys
import os

def getFiles(mydir):
    results = []
    for root,dirs,files in os.walk(mydir):
        for f in files:
            results.append({"name": f, "path": os.path.relpath(os.path.join(root,f))})
    return results

def main():
    mydir = sys.argv[1]
    files = getFiles(mydir)
    files.sort(key=lambda x: os.stat(x["path"]).st_mtime)
    for f in files:
        print f["path"]









if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "Expected 1 parameter 'path'"
        exit()
    else:
        main()
