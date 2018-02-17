/*Scrivere un programma in C “colonnan” che prenda come parametro il pathname di
un file e un numero intero (che
chiameremo n). Il programma deve stampare come output il numero di caratteri
presenti nella n-ma colonna del file se il file e'
un file regolare di testo, non deve stampare nulla negli altri casi. Un file
viene considerato di testo se tutti i suoi byte hanno
valori compresi nel range 1-127. Per controllare se il file e' “regolare” usare
la system call lstat.

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Expected 2 parameters pathname and n ");
    return -1;
  }
  const char *pathname = argv[1];
  int n = atoi(argv[2]);
  FILE *fp = fopen(pathname, "r");
  struct stat sb;

  int c, count, c_column;
  lstat(pathname, &sb);
  if (S_ISREG(sb.st_mode)) {
    // controllare file testo
    while ((c = getc(fp)) != EOF) {
      if (c != EOF && (c > 127 || c < 1)) { // controllo se è un file ASCII
        printf("Non regolare\n");
        return -1;
      }
      if (c == '\n')
        c_column = 0;
      else
        c_column++;
      if (c_column == n) {
        count++;
      }
    }
  }

  printf("%d\n", count);
  fclose(fp);
  return 0;
}
