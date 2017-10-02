#include <sys/syscall.h>
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#define BUF_SIZE 1024

struct linux_dirent{
  long d_ino;
  off_t d_off;
  unsigned short d_reclen;
  char d_name[];
};

int main(int argc, char **argv){
  char path;
  int nread, fd;
  char buf[BUF_SIZE];
  struct linux_dirent *d;
  int bpos;
  char d_type;

  fd = syscall(SYS_open, argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
  if (fd == -1)
    {
       perror("open");
       exit(EXIT_FAILURE);
    }
  for ( ; ; )
    {
      nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
      if (nread == -1)
	{
	  perror("getdents");
	  exit(EXIT_FAILURE);
	}
      if (nread == 0)
	break;
      for (bpos = 0; bpos < nread; )
	{
	  d = (struct linux_dirent *) (buf + bpos);
	  char* out = (char *) d -> d_name;
	  if (strcmp(out, "..") != 0 && strcmp(out, ".") != 0)
	    printf("%s ", out);
	  bpos += d -> d_reclen;
	}
    }
  exit(EXIT_SUCCESS);
}
