#include <pthread.h>
#include <unistd.h>

void *test(void *arg) {
    while(1) {
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    const int NUM = 76;
    pthread_t arr[NUM];

    for (int i = 0; i < NUM; ++i) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, test, NULL);
        pthread_attr_destroy(&attr);
        arr[i] = tid;
    }

    for (int i = 0; i < NUM; ++i) {
        pthread_join(arr[i], NULL);
    }

    //test(NULL);
    return 0;
}
