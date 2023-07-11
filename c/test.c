#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define _EBP( _a ) \
    do { \
        __asm__ __volatile__("mov %%rbp, %%rax; mov 0x8(%%rax), %0;" \
                :"=r"(_a) \
                : \
                :"%rax"); \
    } while (0)

typedef struct {
    int k;
}miwu;

int main(int argn, char** argv)
{
    //printf(" %d\n", 10 >> 0);
    /* int *base = malloc(sizeof(int) * 10); */
    /* for (int i = 0; i < 10; ++i) { */
    /*     base[i] = i; */
    /* } */
    /* int *pos = NULL; */
    /* for (int i = 0; i < 10; ++i) { */
    /*     pos = base + i; */
    /*     free(pos); */
    /* } */
    /* for (int i = 0; i < 10; ++i) { */
    /*     printf("%d\n", base[i]); */
    /* } */

    /* unsigned long a = 0; */
    /* _EBP(a); */
    /* printf("%lu\n", a); */
    /* a = 0b10001; */
    /* _EBP(a); */
    /* printf("%lu\n", a); */

    /* int len = 99990000; */
    /* int a; */
    /* clock_t tick_begin, tick_end; */
    /*  */
    /* tick_begin = clock(); */
    /* for (int i = 0; i < len; ++i) { */
    /*     a = i; */
    /*     a = i + 1; */
    /* } */
    /* tick_end = clock(); */
    /* printf(" cost: %ld\n", tick_end - tick_begin); */
    /*  */
    /* tick_begin = clock(); */
    /* for (int i = 0; i < len; ++i) { */
    /*     a = i; */
    /* } */
    /* for (int i = 0; i < len; ++i) { */
    /*     a = i + 1; */
    /* } */
    /* tick_end = clock(); */
    /* printf(" cost2: %ld\n", tick_end - tick_begin); */
    /*  */

    int a = 10;
    int b = a*0.95 + 0.4;
    printf("b = %d\n", b);

    printf("0x%x\n", 16);
    return 0;
}
