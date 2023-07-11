
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *hstr = "hello";
    char * const dst = (char *)malloc(sizeof(hstr) / sizeof(char));
    memcpy(dst, hstr, sizeof(hstr) / sizeof(char));
    printf("%s\n", dst);
    char *p;
    dst = p;
    return 0;
}
