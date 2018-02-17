
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  time_t now;
  struct group *grentry, *getgrgid(gid_t);
  struct passwd *pwentry, *getpwuid(uid_t);
  struct stat status;
  struct tm *tstr, *localtime(const time_t *);

  if (argc != 2) {
    (void)fprintf(stderr, "usage:\t%s file\n", argv[0]);
    return (1);
  }
  /*      get stat structure for specified file   */
  if (stat(argv[1], &status) == -1) {
    (void)fprintf(stderr, "%s:\tcan't stat %s\n", argv[0], argv[1]);
    return (2);
  }
  /*      display the type of file        */
  if (status.st_mode & S_IFREG)
    (void)fprintf(stdout, "Regular File:\t");
  else if (status.st_mode & S_IFDIR)
    (void)fprintf(stdout, "Directory:\t");
  else if (status.st_mode & S_IFIFO)
    (void)fprintf(stdout, "FIFO Special File:\t");
  else if (status.st_mode & S_IFCHR)
    (void)fprintf(stdout, "Character Special File:\t");
  else if (status.st_mode & S_IFBLK)
    (void)fprintf(stdout, "Block Special File:\t");
  else if (status.st_mode & S_IFLNK)
    (void)fprintf(stdout, "Symbolic Link:\t");
  else
    (void)fprintf(stdout, "Unknown File:\t");
  (void)fprintf(stdout, "%s\n", argv[1]);
  (void)fprintf(stdout, "Inode:\t\t%d\n", (int)status.st_ino);
  (void)fprintf(stdout, "Mode:\t\t%d\n", (int)status.st_mode);
  (void)fprintf(stdout, "Device:\t\t%d\n", (int)status.st_dev);
  (void)fprintf(stdout, "Blocksize:\t%d\n", (int)status.st_blksize);
  (void)fprintf(stdout, "Links:\t\t%d\n", (int)status.st_nlink);
  (void)fprintf(stdout, "Owner (%d):\t", (int)status.st_uid);
  /*      look up owner in /etc/passwd    */
  if ((pwentry = getpwuid(status.st_uid)) == (struct passwd *)NULL) {
    (void)fprintf(stdout, "not found\n");
  } else {
    (void)fprintf(stdout, "%s\n", pwentry->pw_name);
  }
  /*      look up group name in /etc/group        */
  (void)fprintf(stdout, "Group (%d):\t", (int)status.st_gid);
  if ((grentry = getgrgid(status.st_gid)) == (struct group *)NULL) {
    (void)fprintf(stdout, "no found\n");
  } else {
    (void)fprintf(stdout, "%s\n", grentry->gr_name);
  }
  (void)fprintf(stdout, "Size:\t\t%d\n", (int)status.st_size);
  now = status.st_atime;
  tstr = localtime(&now);
  (void)fprintf(stdout, "atime:\t\t%02d:%02d:%02d %02d/%02d/%02d\t",
                tstr->tm_hour, tstr->tm_min, tstr->tm_sec, tstr->tm_mon + 1,
                tstr->tm_mday, tstr->tm_year);
  (void)fprintf(stdout, "(Last Access)\n");
  now = status.st_ctime;
  tstr = localtime(&now);
  (void)fprintf(stdout, "ctime:\t\t%02d:%02d:%02d %02d/%02d/%02d\t",
                tstr->tm_hour, tstr->tm_min, tstr->tm_sec, tstr->tm_mon + 1,
                tstr->tm_mday, tstr->tm_year);
  (void)fprintf(stdout, "(Last Data Modification)\n");
  now = status.st_mtime;
  tstr = localtime(&now);
  (void)fprintf(stdout, "mtime:\t\t%02d:%02d:%02d %02d/%02d/%02d\t",
                tstr->tm_hour, tstr->tm_min, tstr->tm_sec, tstr->tm_mon + 1,
                tstr->tm_mday, tstr->tm_year);
  (void)fprintf(stdout, "(Last File Status Change)\n");
  return (0);
}
