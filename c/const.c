
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_func(const char *str) {
    printf("%x\n", str);
    str = "world";
    printf("%x\n", str);
    printf("%s\n", str);
}

int main() {
    const char *hstr = "hello";
    char *str = (char*)malloc(strlen(hstr) * sizeof(char));
    memcpy(str, hstr, strlen(hstr) * sizeof(char));
    //print_func(NULL);
    char * const * c_ptr = &str;
    (*c_ptr)[0] = 'i';
    printf("%s\n", *c_ptr);
    c_ptr = NULL;

    const int ** pp;
    int *p;
    pp = &p;
    return 0;
}
