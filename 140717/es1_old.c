#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

const char *get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot + 1;
}

int main(int argc, char const *argv[]) {
  DIR *dir;
  struct dirent *entry;
  char *command = "gcc -I. -ggdb -c ";
  char *argument;
  char *final_command;
  struct tm *foo;
  struct stat attrib;

  dir = opendir(".");
  if (dir != NULL) {
    while ((entry = readdir(dir)) != NULL) {
      if (strcmp(get_filename_ext(entry->d_name), "c") == 0) {
        // if  esiste file.o &&file.o è più recente di file.c
        stat(argument, &attrib);

        foo = gmtime(&(attrib.st_mtime));
        printf("Year: %d\n", foo->tm_year);
        argument = entry->d_name;

        foo.actime = foo.st_atime;      /* keep atime unchanged */
        new_times.modtime = time(NULL); /* set mtime to current time */
        if (utime(filename, &new_times) < 0) {
          perror(filename);

          final_command = malloc(strlen(command) + strlen(argument));
          strcpy(final_command, command);
          strcat(final_command, argument);
          printf("%s\n", final_command);
          system(final_command);
        }
      }
      closedir(dir);
    }
    else {
      perror("Cannot open current dir");
    }
    return 0;
  }
