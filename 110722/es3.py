import os,sys

if len(sys.argv) < 3:
    print "Expected 2 parameters"
    exit()

def extensions(file):
    return os.path.splitext(file)[1]

def search_files(path):
    results = []
    for root,dirs,files in os.walk(path):
        for f in files:
            if extensions(f) == ".c" or extensions(f) == ".h":
                results.append({"name":f,"path":os.path.abspath(os.path.join(root,f))})
    return results


path1 = sys.argv[1]
path2 = sys.argv[2]
files1 = search_files(path1)
files2 = search_files(path2)


for f1 in files1:
    if f1["name"] not in files2:
        print("{} not in {}").format(f1["path"],path2)
"""
for f1 in files1:
    with open(f1["path"]) as file1:
        for f2 in files2:
            if not os.path.samefile( f1["name"], f2["name"]):
                print("{} not in {}").format(f1["path"],path2)
            else:
                with open(f2["path"]) as file2:
                    if file1.read() != file2.read():
                        print("{}  {} differ").format(f1["path"],f2["path"])
"""
