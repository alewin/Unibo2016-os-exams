//Scrivere un programma che preso come parametro un file contenente un elenco di comandi (con I relativi parametri) li attivi tutti in esecuzione concorrente e rimanga in attesa. Quando il primo termina, vengono terminati (con segnale SIGTERM) tutti gli altri. (consiglio: puo' essere utile usare la mia libreria s2argv-execs)
// esempio: wta commands
//il file commands contiene:
//./ttest 40
//./ttest 10
//./ttest 20
//lo script ./ttest contiene:
//#!/bin/bash
//echo waiting for $1 seconds
//sleep $1
//echo done $i
//l'ouptut sara':
//waiting for 40 seconds
//waiting for 10 seconds
//waiting for 20 seconds
//done 10
//e poi basta perche' gli altri processi verranno terminati.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return (EXIT_FAILURE);
  }
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 1;
  const char *pathname = argv[1];

  stream = fopen(pathname, "r");
  if (stream == NULL)
    exit(EXIT_FAILURE);

  while (((read = getline(&line, &len, stream)) != -1) & (i <= 2)) {
    printf("Retrieved line %d of length %zu :\n", i, read);
    printf("%s", line);
    i++;
  }

  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}
