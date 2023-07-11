
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char * temp = (char *)malloc(5);
    const char ** dst = &temp;
    const char * hstr = "hello";
    dst = &hstr;
    *dst = hstr;
    printf("%s\n", *dst);
    (*dst)[0] = 'i';
    (*dst)[1] = 'i';
    return 0;
}
