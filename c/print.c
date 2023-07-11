
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char **argv) {
    char name[100] = {0};
    char buff[101] = {0};
    sprintf(buff, "name: %s\n", name);
    printf("%s-1 == %d%%\n", buff, (int)(0xffffffff));
    return 0;
}


