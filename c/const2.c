
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *hstr = "hello";
    hstr = "world";
    hstr[0] = 'i';
    hstr[1] = 'i';
    return 0;
}
