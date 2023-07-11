#include <stdio.h>
#include <stdlib.h>

void test(int w) {
    printf("%d\n", w);
}

#define value 1e-4f

int main() {
    float w = 155.5;
    test(w/100);
    test(w/100 + 0.5);
    int w2 = w/100 + 0.5;
    test(w2);
    printf("%f\n", value);
    return 0;
}
