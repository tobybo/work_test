
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int a,b,c,d,e,f,g; // 28 bytes
}test2;

typedef struct {
    uint8_t val;
    int val2;
    test2 tt;
}test;

typedef struct {
    double val2;
    int val[7];
}test3;

typedef struct {
    int val;
}test4;

typedef struct {
    char val;
}test5;

typedef struct {
    int val;
}test6;

typedef struct {
    long val;
}test7;

union test8 {
    char a[10];
    int b;
};

typedef struct {
    char a;
    long b;
    char c;
}test9;

typedef struct {
    int val[11];
}test11;

typedef struct {
    char a;
    long b;
    long c;
}test10;

int main(int argc, char *argv[])
{
    test t = {.val = 125, .val2 = 0x01111111};
    *(int*)((char*)&t.val + 1) = 10;
    printf("val: %c,%d, val2: %d\n", t.val, t.val, t.val2);
    //*((char*)&(t.val) + 1) = 3;
    printf("val: %c,%d, val2: %d, valhide: %d\n", t.val, t.val, t.val2, *((char*)&(t.val) + 1));
    printf("sizeof test: %lu, sizeof test2: %lu\n", sizeof(test), sizeof(test2));
    test3 *ptr3 = calloc(sizeof(test3), 1);
    printf("sizeof test3: %lu, addr: 0x%x\n", sizeof(test3), ptr3);
    test4 *ptr4 = calloc(sizeof(test4), 1);
    printf("sizeof test4: %lu, addr: 0x%x\n", sizeof(test4), ptr4);

    test6 *ptr6 = calloc(sizeof(test6), 1);
    printf("sizeof test6: %lu, addr: 0x%x\n", sizeof(test6), ptr6);
    test7 *ptr7 = calloc(sizeof(test7), 1);
    printf("sizeof test7: %lu, addr: 0x%x\n", sizeof(test7), ptr7);

    union test8 t8;
    int *p = (int*)&(t8.a[1]);
    *p = 17;
    printf("t8->b: %x\n", t8.b);

    test9 *ptr9 = malloc(sizeof(test9));
    printf("sizeof test9: %lu, addr: 0x%x\n", sizeof(test9), ptr9);

    test11 *ptr11 = malloc(sizeof(test11));
    printf("sizeof test11: %lu, addr: %lu, val8addr: %lu\n", sizeof(test11), ptr11, &ptr11->val[8]);

    int *ptr5 = malloc(4);
    *ptr5 = 0;
    ptr11->val[8] = -1;
    int addr_eq = &ptr11->val[8] == ptr5;
    printf("sizeof test5: %lu, addr: %lx, val: %d, val8: %d, eq: %d\n", sizeof(*ptr5), ptr5, *ptr5, ptr11->val[8], addr_eq);

    test10 *ptr10 = calloc(sizeof(test10), 1);
    printf("sizeof test10: %lu, addr: 0x%lx\n", sizeof(test10), ptr10);

    printf("sizeof long: %lu, long long: %lu, size_t: %lu\n", sizeof(long), sizeof(long long), sizeof(size_t));

    free(ptr3);
    free(ptr4);
    free(ptr5);
    free(ptr6);
    free(ptr7);
    free(ptr9);
    return 0;
}
