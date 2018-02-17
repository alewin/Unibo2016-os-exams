#!/usr/bin/env python3
"""lo script deve creare una sottodirectory per ogni suffisso che compare nei file
della directory corrente (e.g. Se sono presenti file a.pdf, b.odt, c.png, d.pdf, e.odt, f.pdf, g, h deve creare le
directory .pdf .odt .png) e
per ogni file con suffisso deve creare un link simbolico per poter accedere tutti i file
con lo stesso suffisso a partire dalla directory relativa al suffisso. (nell'esempio precendente .pdf deve contenere
tre link simbolici a.pdf, d.pdf, f.pdf che puntano ai corrispondenti file)."""
import os

ext = dict()


dirs = os.listdir(".")

for cur_file in dirs:
    if(cur_file[0]!= "."):

        filename, file_extension = os.path.splitext(cur_file)
        print file_extension
        if not os.path.exists(file_extension):
            print "creo cartella"
            os.mkdir(file_extension)
        
        dst = os.path.join(os.path.abspath(file_extension),cur_file)
        cur_file = os.path.abspath(cur_file)
        os.symlink(cur_file,dst)
