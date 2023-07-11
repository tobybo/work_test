
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

struct test {
    int c[3];
    int d;
};

unsigned long TICK()
{
    unsigned int lo,hi;
    __asm__ __volatile__ (
            "rdtsc":"=a"(lo),"=d"(hi)
            );
    return ((unsigned long)hi) << 32 | lo;
}

int main(int argc, char **argv) {
    int a[3];
    int b[3] = {0};
    struct test c = {0};
    struct test *e = malloc(sizeof(c));
    *e = (struct test){0};
    for (int i = 0; i < 3; ++i) {
        printf("a[%d] = %d\n", i, a[i]);
        printf("b[%d] = %d\n", i, b[i]);
        printf("test.c[%d] = %d\n", i, c.c[i]);
        printf("e.c[%d] = %d\n", i, e->c[i]);
    }
    printf("test.d = %d\n", c.d);
    printf("e.d = %d\n", e->d);

	int k;
    scanf("%d", &k);
    unsigned long begin = TICK()/1000;
	for (int i = 0; i < k; ++i) {
        int old[100] = {0};
    }
    unsigned long end = TICK()/1000;
    printf("old init, time,%lu\n", end - begin);
    begin = end;
    for (int i = 0; i < k; ++i) {
        int new[100];
        memset(new, 0, sizeof(new));
    }
    end = TICK()/1000;
    printf("new init, time,%lu\n", end - begin);
    return 0;
}
