#include "myclass.h"

int api_find_road(int x, int z) {
    myclass mc(x, z);
    return mc.find_road();
}
