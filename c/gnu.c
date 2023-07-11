#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <asm-generic/int-ll64.h> // for __u16
#include <linux/swab.h> // for __fswab16

#define min(x, y) ({ \
        typeof(x) _min1 = (x); \
        typeof(y) _min2 = (y); \
        (void) (&_min1 == &_min2); \
        _min1 < _min2 ? _min1: _min2; })

#define swab16(x) \
    (__builtin_constant_p((__u16) (x)) ? \
    ___constant_swab16(x) : \
    __fswab16(x))

int main(int argc, char *argv[])
{
    int a = 10;
    int b = 11;
    int c = min(a, b);

    float d = 11.0;
    float e = 11.1;
    float f = min(d, d);

    const uint16_t x = 0x1001;

    printf("c: %d, f: %f, x: 0x%x\n", c, f, x);
    int _x = swab16(x);
    printf("c: %d, f: %f, x: 0x%4x\n", c, f, _x);
    return 0;
}
