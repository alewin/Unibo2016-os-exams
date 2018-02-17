import os,sys,re
initd_files = list(os.listdir("/etc/init.d"))
inif = {}
for x in  initd_files:
    inif[x] = ""

for rc in os.listdir("/etc/"):
    if os.path.isdir(os.path.join("/etc",rc)) and re.match('rc.*\.d$',rc):
        files = os.listdir(os.path.join("/etc",rc))
        for f in files:
            pref,file = f[:3],f[3:]
            if file in initd_files:
                inif[file] += pref + " "

for x in inif:
    print x + " " +inif[x]
