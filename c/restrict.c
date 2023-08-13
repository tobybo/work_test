
#include <stdio.h>
#include <stdlib.h>


int main(int argc, const char** argv) {

    int a = 10;
    /* toby@2023-08-06): just tell complier sth, not really restrict on it */
    int * restrict b = &a;
    int *c = b;
    *c = 15;

    printf("%d\n", *b);

    return 0;
}
