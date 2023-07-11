#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <coroutine.h>

typedef struct coroutine {
    void *callee;
    void *caller;
    void *saved_sp;
} coroutine_t;

void coroutine_init(coroutine_t *coro, void *callee) {
    coro->callee = callee;
    coro->caller = NULL;
    coro->saved_sp = NULL;
}

void coroutine_yield(coroutine_t *coro) {
    coro->caller = __builtin_coro_save(&coro->saved_sp);
    __builtin_coro_resume(coro->callee, coro->caller, &coro->saved_sp);
}

void coroutine_resume(coroutine_t *coro) {
    __builtin_coro_resume(coro->caller, coro->saved_sp, &coro->saved_sp);
}

__attribute__((__coroutine__))
void timer(int seconds) {
    time_t start = time(NULL);
    while (time(NULL) - start < seconds) {
        coroutine_yield(__builtin_coro_save(&start));
    }
}

int main() {
    coroutine_t coro;
    coroutine_init(&coro, timer(&coro, 5));
    while (__builtin_coro_resume(&coro, NULL, NULL)) {
        printf("tick\n");
    }
    printf("done\n");
    return 0;
}
