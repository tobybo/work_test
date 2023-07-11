
#include <stdlib.h>
#include <stdio.h>

#include "define_test.h"

int gLand[WIDTH][WIDTH];

int main(int argc, char *argv[])
{
    for (int i = 0; i < TIMES; ++i) {
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < WIDTH; ++y) {
                gLand[y][x] = 1;
            }
        }
    }
    return 0;
}
