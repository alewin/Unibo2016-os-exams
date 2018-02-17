import os,sys


for f in os.listdir("."):
    extension = (os.path.splitext(f)[1])[1:]
    if os.path.isfile(f):
        if not os.path.exists(extension):
            os.mkdir(extension)
        dst = os.path.join(os.path.abspath(extension),f)
        src = os.path.abspath(f)
        os.symlink(src,dst)
