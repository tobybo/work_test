
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    int count = 0;
    for (int i = 0; i < 65535; ++i) {
        fd = dup(1);
        if (fd > 0) {
            count++;
        }
    }
    printf("succ count,%d\n", count);
    return 0;
}
