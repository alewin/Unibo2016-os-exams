#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

off_t fsize(const char *filename) {
  struct stat st;
  if (stat(filename, &st) == 0)
    return st.st_size;
  fprintf(stderr, "Cannot determine size of %s: %s\n", filename,
          strerror(errno));
  return -1;
}

// usage   char **files = NULL; int n =  dynamic_get_files(pathname, &files);
int dynamic_get_files(char *pathname, char ***files) {
  DIR *dir;
  int i = 0;
  struct dirent *ent;
  if ((dir = opendir(pathname)) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_type == DT_REG) {
        *files = (char **)realloc(*files, (i + 1) * sizeof(char *));
        (*files)[i] = (char *)malloc((strlen(ent->d_name)) + 1);
        strcpy((*files)[i], ent->d_name);
        i++;
      }
    }
    closedir(dir);
  }
  return i;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Expected 1 parameter");
    return -1;
  }
  char *pathname = argv[1];
  char **files = NULL;
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i;
  int n = dynamic_get_files(pathname, &files);
  for (int j = 0; j < n; j++) {
    printf("%d - %s\n", fsize(files[j]), files[j]);
    i = 1;
    stream = fopen(files[j], "r");
    if (stream == NULL)
      exit(EXIT_FAILURE);

    while (((read = getline(&line, &len, stream)) != -1)) {
      printf("%s", line);
      i++;
    }
  }
  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
  return 1;
}
