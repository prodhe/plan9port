#define getpts not_using_this_getpts
#include "bsdpty.c"
#undef getpts

int
getpts(int fd[], char *slave)
{
       fd[1] = posix_openpt(ORDWR);
       if (fd[1] >= 0) {
               grantpt(fd[1]);
               unlockpt(fd[1]);
               fchmod(fd[1], 0620);
               strcpy(slave, ptsname(fd[1]));
               if ((fd[0] = open(slave, ORDWR)) >= 0)
                       return 0;
               close(fd[1]);
       }
       sysfatal("no ptys");
       return 0;
}
