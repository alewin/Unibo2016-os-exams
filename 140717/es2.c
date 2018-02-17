#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*
  perogni file.c inside directory
    if esiste file.o  && file.o è più recente di file.c
        gcc file.c => file.o
 */

const char *get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot + 1;
}

void ggg() {
  DIR *dir;
  struct dirent *ent;
  char *command[10];
  command[0] = "gcc -I. -ggdb -c ";

  dir = opendir(".");
  if (dir != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (strcmp(get_filename_ext(ent->d_name), "c") == 0) {
        printf("%s\n", ent->d_name);
        // if  esiste file.o &&file.o è più recente di file.c
      }
    }
    closedir(dir);
  } else {
    perror("Cannot open current dir");
  }
}

int main(int argc, char const *argv[]) {
  ggg();
  return 0;
}
