/*Esercizio 1: Linguaggio C (obbligatorio): (20 punti)
  Scrivere un programma che per ogni file .c nella directory corrente chiami il
compilatore gcc per generare il file oggetto (.o) a
  meno che esista gia' nella directory un file oggetto relativo allo stesso
sorgente che sia piu' nuovo (ultima modifica) del
  sorgente.
  Tutti I parametri devono essere passati al compilatore.
Es:
genobj -I . -ggdb
se nella directory corrente esistono I file uno.c e due.c e il file due.o deve
richiamare
gcc -I. -ggdb -c uno.c
e, solo se due.o ha ultima modifica precedente a due.c, deve chiamare
gcc -I. -ggdb -c due.c
*/

#include <dirent.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define MAX_ENTR 1000

int get_dir_files(DIR *dir_stream, char *name[NAME_MAX]) {

  struct dirent *ent;

  if ((ent = readdir(dir_stream)) == NULL) {
    return -1;
  } else {
    if (ent->d_type != DT_DIR && ent->d_name[0] != '.') {
      if (ent->d_name[strlen(ent->d_name) - 2] == '.' &&
          ent->d_name[strlen(ent->d_name) - 1] == 'c') {

        *name = ent->d_name;
        return 0;
      } else if (ent->d_name[strlen(ent->d_name) - 2] == '.' &&
                 ent->d_name[strlen(ent->d_name) - 1] == 'o') {
        *name = ent->d_name;
        return 1;
      } else
        return 2;
    } else
      return 2;
  }
}

int is_older(char *file1[NAME_MAX], char *file2[NAME_MAX]) {
  struct stat *buf;
  struct stat *buf2;
  int s;

  lstat(*file1, buf);
  lstat(*file2, buf2);

  /*return  (buf.st_mtime < buf2.st_mtime2) ? 0 : 1;*/
  return 0;
}

void call_gcc(char *file1[NAME_MAX]) {}

int main(int argc, char *argv[]) {
  DIR *dir = NULL;
  char *current_file[NAME_MAX];
  char *(*all_cfiles[MAX_ENTR]);
  char *(*all_ofiles[MAX_ENTR]);
  int n;
  int i = 0;
  int t = 0;
  int s = 0;
  if (argc < 2) {

    printf("usage: %s directory [flags]", argv[0]);
    exit(EXIT_FAILURE);
  } else {

    if ((dir = opendir(argv[1])) == NULL) {
      printf("Error wile opening the directory stream. Aborting!");
      exit(EXIT_FAILURE);
    };
    while ((n = get_dir_files(dir, current_file)) != -1) {
      if (n != 2) {
        if (n == 0) {
          all_cfiles[i] = malloc(sizeof(current_file + 1));
          all_cfiles[i] = current_file;
          printf("returned:%d read C:%s\n", n, *all_cfiles[i]);
          i++;
        } else if (n == 1) {
          all_ofiles[t] = malloc(sizeof(current_file + 1));
          all_ofiles[t] = current_file;
          printf("returned:%d read O:%s\n", n, *all_ofiles[t]);
          t++;
        }
      }
    }

    // WTF????????!!!!! DOVREBBERO ESSERCI I FILE C!!!
    while (s < i) {
      printf("C FILES:%s\n", *all_cfiles[s]);

      s++;
    }
    printf("You have %d .c files and %d .o files in the directory %s\n", i, t,
           argv[1]);

    for (int j = 0; j < i; j++) {
      int z = 0;

      printf("analyzing %s\n", *all_cfiles[j]);
      while (z < t) {
        if (strlen(*all_cfiles[j]) == strlen(*all_ofiles[z])) {
          printf("EQUAL\n");
          if ((strncmp(*all_cfiles[j], *all_ofiles[z],
                       (strlen(*all_cfiles[j]) - 1))) == 0) {
            printf("%s corresponds to %s\n", *all_cfiles[j], all_ofiles[z]);
          }
        }
        z++;
      }
    }

    closedir(dir);
  }
  return 0;
}
