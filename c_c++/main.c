#include "stdio.h"
#include "stdlib.h"
#include "wrapper.h"

int main() {
    int ret = c_api_find_road(1, 1);
    printf("road_ret, %d\n", ret);
    return 0;
}
