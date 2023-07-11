
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char * temp = (char *)malloc(5);
    char * const * dst = &temp;
    char * p;

    (*dst)[0] = 'i';
    dst = &p;
    *dst = p;

    return 0;
}
