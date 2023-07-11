

#include <stdlib.h>
#include <stdio.h>

#define CHAR_MASK 0xFF

int main(int argc, char *argv[])
{
    char c = -27;
    unsigned int a = c; // char 转为 unsigned int/int 会用 c 的符号位填充高位
    unsigned char b = c;
    int d = c;
    printf("负数char %d -> unsigned char %x\n", c, b);
    printf("负数char %d -> int %x\n", c, d);
    printf("负数char %d -> unsigned int %x\n", c, a);
    //printf("a: %u\n", a & CHAR_MASK);
    return 0;
}
