#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static int sum = 0;

void *thread_get(void *arg) {
    printf("thread_get, before lock, idx: %lu\n", arg);
    pthread_mutex_lock(&lock);
    printf("thread_get, before wait, idx: %lu\n", arg);
    pthread_cond_wait(&cond, &lock);
    printf("thread_get, after wait, idx: %lu\n", arg);
    pthread_mutex_unlock(&lock);
    printf("thread_get, after lock, idx: %lu\n", arg);
    return NULL;
}

void *thread_put(void *arg) {
    while (1) {
        printf("thread_put, before lock, idx: %lu\n", arg);
        pthread_mutex_lock(&lock);
        pthread_mutex_unlock(&lock);
        printf("thread_put, after lock, idx: %lu\n", arg);
        pthread_cond_broadcast(&cond);
        printf("thread_put, after signal, idx: %lu\n", arg);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    /*
     * 1. 创建 n 个 get 线程
     * 2. 创建 1 个 put 线程
     * 3. 观察是否同时唤醒了多个线程 只唤醒了一个
     * 4. 观察 broadcast 被唤醒的线程是否需要先后获得锁 是的
     * */
    for (long i = 0; i < 3; ++i) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, thread_get, (void *)(i + 1));
        pthread_attr_destroy(&attr);
    }
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, thread_put, (void *)0);
    pthread_attr_destroy(&attr);

    while (1) {
        sleep(2);
    }
    return 0;
}
