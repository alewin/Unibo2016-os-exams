#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE + 16))

int main(int argc, char const *argv[]) {

  if (argc < 2) {
    printf("%s necessità due parametri \n", argv[0]);
    return -1;
  }
  const char *pathname = argv[1];
  int i, fd, wd, len;
  char buf[BUF_LEN];

  fd = inotify_init();
  wd = inotify_add_watch(fd, pathname, IN_CREATE);
  while (1) {

    while (i < len) {
      struct inotify_event *event = (struct inotify_event *)&buf[i];
      if (event->len) {
        if ((event->mask & IN_CREATE) && !(event->mask & IN_ISDIR)) {
          printf("The file %s was creaated \n", event->name);

          struct stat sb;
          stat(event->name, &sb);
          if (S_IXUSR & sb.st_mode) {
            // execv(event->name);
            remove(event->name);
            printf("The file %s was removes \n", event->name);
          }
        }
      }
      i += EVENT_SIZE + event->len;
    }
    len = read(fd, buf, sizeof(buf));
    i = 0;
  }
  inotify_rm_watch(fd, wd);
  close(fd);
  return 0;
}
