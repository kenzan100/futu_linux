#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open_fd(const char * path);
static void do_cat(const int fd, const char *path);
static void die(const char *s);


int
main(int argc, char *argv[])
{
  int i;
  int fd;

  if (argc < 2) {
    do_cat(STDIN_FILENO, "stdin");
    exit(1);
  }
  for (i = 1; i < argc; i++) {
    fd = open_fd(argv[i]);
    do_cat(fd, argv[i]);
  }
  exit(0);
}

int
open_fd(const char * path)
{
  int fd;
  fd = open(path, O_RDONLY);
  return fd;
}

#define BUFFER_SIZE 2048

static void
do_cat(const int fd, const char *path)
{
  unsigned char buf[BUFFER_SIZE];
  int n;

  if (fd < 0) die(path);
  for (;;) {
    n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }
  if (close(fd) < 0) die(path);
}

static void
die(const char *s)
{
  perror(s);
  exit(1);
}
