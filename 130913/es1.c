#include <dirent.h>
#include <limits.h> //For PATH_MAX
#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

char pathbuf[PATH_MAX + 1];
char *realpath(const char *restrict file_name, char *restrict resolved_name);

char *read_from_file(const char *filename) {
  long int size = 0;
  FILE *file = fopen(filename, "r");

  if (!file) {
    fputs("File error.\n", stderr);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);

  char *result = (char *)malloc(size);
  if (!result) {
    fputs("Memory error.\n", stderr);
    return NULL;
  }

  if (fread(result, 1, size, file) != size) {
    fputs("Read error.\n", stderr);
    return NULL;
  }

  fclose(file);
  return result;
}
int getFiles(const char *pathname, char **array) {
  DIR *d;
  struct dirent *ent;

  int i = 0;
  if ((d = opendir((const char *)pathname)) != NULL) {
    while ((ent = readdir(d)) != NULL) {
      if (ent->d_type == DT_REG) {
        realpath(pathname, pathbuf);
        strcpy(pathbuf, strcat(strcat(pathbuf, "/"), ent->d_name));
        array[i] = malloc(255);
        strcpy(array[i], pathbuf);
        i++;
      }
    }
  } else {
    exit(-1);
  }
  return i;
}
unsigned long hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

int main(int argc, char const *argv[]) {
  char **files = malloc(sizeof(char *) * 5);
  int n_files = getFiles(argv[1], files);
  char *content1, *content2;
  for (int i = 0; i < n_files; i++) {
    printf("%d) %s \n", i, files[i]);
  }
  for (int i = 0; i < n_files; i++) {
    content1 = read_from_file(files[i]);
    for (int j = i; j < n_files; j++) {
      if (i != j) {
        content2 = read_from_file(files[j]);
        if ((strcmp(content1, content2)) == 0) {
          printf("file %s è uguale a file %s", files[i], files[j]);
          remove(files[j]);
          symlink(files[i], files[j]);
        }
      }
    }
  }
  return 0;
}

/*  files = realloc(files, (i + 1) * sizeof(*files));
  ++i;

  // Allocate memory for the new string item in the array
  files[i - 1] = malloc(254 * sizeof(char *));

  // Populate a new value in the array
  strcpy(files[i - 1], "string 3"); //*/
