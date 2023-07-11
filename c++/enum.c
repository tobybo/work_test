
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char ** argv) {
    enum {
        NODE_LIST_ACTION_INIT = 0,
        NODE_LIST_ACTION_FETCH = 1,
        NODE_LIST_ACTION_PUTBACK = -1,
    };
    printf("init,%d, fetch,%d, putback,%d\n", NODE_LIST_ACTION_INIT, NODE_LIST_ACTION_FETCH, NODE_LIST_ACTION_PUTBACK);
    return 0;
}
