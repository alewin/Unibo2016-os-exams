import os
import sys

def getFilesContent():
    res = []
    for root,dirs,files in os.walk("./prova"):
        for f in files:
            r = open("./prova/" +f,"r")
            res.append({"name": f, "content": r.read()})
            r.close()
    return res

dict_files_content =  getFilesContent()
print dict_files_content

for x in dict_files_content:
    for y in dict_files_content:
        if x["name"] != y["name"]:
            if x["content"] == y["content"]:
                print x["name"] + " - "+ y["name"]
