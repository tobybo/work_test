#include <stdio.h>
#include <stdlib.h>

int main() {
    char buf[3];
    buf[2] = 'A';
    int test = 1;
    sprintf(buf, "%02x", test);
    printf("%c\n", *buf);
    printf("%c\n", *(buf + 1));
    printf("%c\n", *(buf + 2));
    return 0;
}
