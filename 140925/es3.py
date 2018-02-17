#Scrivere un programma python o uno scrip bash che faccia un backup storico di un file.
# backn file n
#deve mantenere n versioni del file specificato. n>2 Esempio:
#backn miofile 10
#se esiste miofile.9 deve essere rinominato in miofile.10
#se esiste miofile 8 deve essere rinominato in miofile 9
#e cosi' via fino a miofile.2, rinominato miofile 3.
#ora se miofile.1 ha lo stesso contenuto di miofile.3,
#miofile diventa un link fisico a miofile.2 miofile viene copiato in miofile.1

"""
if read(myfile1) == read(myfile3)
    link(miofile,miofile2)
    myfile1 = read(myfile)

"""
#!/usr/bin/python
import sys
import os


def create_backups(myfile, n):
    for i in range(1,n): #n=10 controllo da myfile1 a myfile9
        if os.path.isfile(myfile)

        back = open(myfile,"w+")
        back.write()


if len(sys.argv) < 3
    print "Expected 2 parameters, first is the file, second is the number of version"
    exit()
else if sys.argv[2] < 2
    print "The second parameter must be greater than 2"
    exit()

create_backups(sys.argv[1],sys.argv[2])


    out_file = open("test.txt","w")
out_file.write("This Text is going to out file\nLook at it and see\n")
out_file.close()
