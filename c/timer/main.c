#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <timer.h>
#include <unistd.h>

int gOn;
unsigned long gMsec;
int gTimeControl;
unsigned int gTmNum;

void *threadTime(void *arg) {
    static int init;
    static struct timeval tsNow, tv;
    static struct timeval tmStart;

    gettimeofday(&tsNow, NULL);
    if (!init) {
        init = 1;
        tmStart.tv_sec = tsNow.tv_sec + 1;
        gMsec = 0;
        tv.tv_usec = 1000000 - tsNow.tv_usec;
        select(0, NULL, NULL, NULL, &tv);
    }

    while (gOn) {
        tv.tv_usec = 1000 - (tsNow.tv_usec % 1000);
        select(0, NULL, NULL, NULL, &tv);
        gettimeofday(&tsNow, NULL);
        gMsec = (tsNow.tv_sec - tmStart.tv_sec) * 1000 + tsNow.tv_usec / 1000;
    }
}

int main(int argc, char *argv[])
{
    gOn = 1;

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, threadTime, NULL);
    pthread_attr_destroy(&attr);

    start_timer();

    add_timer(-1, 1, 1);
    // add_timer(2580, 1, 1);
    // add_timer(163840, 2, 1);

    sleep(200);
    return 0;
}
