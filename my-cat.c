#include <sys/syscall.h>
#include <stdio.h>
#include <errno.h>
#include <sys/file.h>
#include <unistd.h>

int main(int charc, char **argv){
  char buffer[BUFSIZ];
  char *path = argv[1];
  int fd = 0;
  fd = syscall(SYS_open, path, O_RDONLY, 0);
  int nbyte = syscall(SYS_read, fd, buffer, BUFSIZ);
  syscall(SYS_write, 1, buffer, nbyte);
  //  printf("The file descriptor was %d", fd);
  syscall(SYS_close, fd);
  return 0;
}
