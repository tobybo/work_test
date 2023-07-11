#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/prctl.h>
#include <pthread.h>
#include <sys/time.h>

#include "timer.h"
#include "que.h"

static unsigned int gStartSec = 0;

extern int gOn;
extern unsigned long gMsec;
extern int gTimeControl;
extern unsigned int gTmNum;

static unsigned long gStartMsec;
static long timer_jiffies= 0;
static struct timer_vec tv5;
static struct timer_vec tv4;
static struct timer_vec tv3;
static struct timer_vec tv2;
static struct timer_vec_root tv1;
static struct timer_vec * tvecs[5];
static int count = 0;

#define MAX_LUA_THREAD_NUM 1

Que gQueTimerPut;
Que gQueTimerGet[MAX_LUA_THREAD_NUM];

long frame(unsigned long now)
{
    return ( now - gStartMsec ) / TIMER_TICK;
}

void handle(timer_list *timer)
{
    printf("time_step, handle, timer,%ld, expire,%ld, timer_jiffies,%ld, msec,%ld, startmsec,%ld\n", timer->id, timer->expires, timer_jiffies, gMsec, gStartMsec);

    free( timer );
}

void initTimer()
{
    tvecs[0] = (struct timer_vec*)&tv1;
    tvecs[1] = &tv2;
    tvecs[2] = &tv3;
    tvecs[3] = &tv4;
    tvecs[4] = &tv5;

    int i;
    for (i = 0; i < TVN_SIZE; i++) {
        INIT_LIST_HEAD(tv5.vec + i);
        INIT_LIST_HEAD(tv4.vec + i);
        INIT_LIST_HEAD(tv3.vec + i);
        INIT_LIST_HEAD(tv2.vec + i);
    }

    for (i = 0; i < TVR_SIZE; i++) {
        INIT_LIST_HEAD(tv1.vec + i);
    }

    gStartMsec = gMsec;
    timer_jiffies= 0;
    tv1.index = 0;
    tv2.index = 0;
    tv3.index = 0;
    tv4.index = 0;
    tv5.index = 0;
    count = 0;
}

void internal_add_timer(timer_list *timer)
{
    /*
     * must be cli-ed when calling this
     */
    //LOG("[TIMER_ADD], sn = %-4d, cycle = %-5d, expires = %-8d", timer->id, timer->cycle, timer->expires);

    unsigned long expires = timer->expires;
    long idx = expires - timer_jiffies;
    if ( gTimeControl ) {
        if ( idx < 0 ) {
            timer->expires = timer_jiffies;
            idx = 0;
        }
    } else {
        if (idx < 1) {
            timer->expires = timer_jiffies + 1;
            idx = 1;
        }
    }

    struct list_head * vec;

    int i = 0;
    if (idx < TVR_SIZE) {
        i = expires & TVR_MASK;
        vec = tv1.vec + i;
        printf("idx < TVR_SIZE, idx: %ld, expires: %x, i,%d\n", idx, expires, i);
    } else if (idx < 1 << (TVR_BITS + TVN_BITS)) {
        i = (expires >> TVR_BITS) & TVN_MASK;
        vec = tv2.vec + i;
    } else if (idx < 1 << (TVR_BITS + 2 * TVN_BITS)) {
        i = (expires >> (TVR_BITS + TVN_BITS)) & TVN_MASK;
        vec =  tv3.vec + i;
    } else if (idx < 1 << (TVR_BITS + 3 * TVN_BITS)) {
        i = (expires >> (TVR_BITS + 2 * TVN_BITS)) & TVN_MASK;
        vec = tv4.vec + i;
    } else if ((signed long) idx < 0) {
        /* can happen if you add a timer with expires == jiffies,
         * or you set a timer to go off in the past
         */
        vec = tv1.vec + tv1.index;
    } else if ((unsigned long)idx <= 0xffffffffUL) {
        i = (expires >> (TVR_BITS + 3 * TVN_BITS)) & TVN_MASK;
        vec = tv5.vec + i;
    } else {
        /* Can only get here on architectures with 64-bit jiffies */
        INIT_LIST_HEAD(&timer->link);
        return;
    }
    /*
     * Timers are FIFO!
     */

    LIST_ADD(&timer->link, vec->prev);
}


void cascade_timers(struct timer_vec *tv)
{
    /* cascade all the timers from tv up one level */
    struct list_head *head, *curr, *next;

    head = tv->vec + tv->index;
    curr = head->next;
    /*
     * We are removing _all_ timers from the list, so we don't  have to
     * detach them individually, just clear the list afterwards.
     */
    while (curr != head) {
        timer_list *tmp;

        tmp = LIST_ENTRY(curr, timer_list, link);
        next = curr->next;
        LIST_DEL_INIT(curr); // not needed
        internal_add_timer(tmp);
        curr = next;
    }
    INIT_LIST_HEAD(head);
    tv->index = (tv->index + 1) & TVN_MASK;
}


void run_timer_list(unsigned long curMsec)
{
    long curFrame = frame(curMsec);
    int i,n;
    struct list_head *head, *curr;
    for (i = 0; i < 65536; ++i) {
        if ((long)(curFrame - timer_jiffies) >= 0) {

            if (!tv1.index) {
                n = 1;
                do {
                    cascade_timers(tvecs[n]);
                } while (tvecs[n]->index == 1 && ++n < NOOF_TVECS);
            }
            head = tv1.vec + tv1.index;
            curr = head->next;
            while (curr != head) {
                timer_list *timer;
                timer = LIST_ENTRY(curr, timer_list, link);

                curr = curr->next;
                LIST_DEL_INIT(curr->prev);

                handle( timer );
                count--;
            }
            ++timer_jiffies;
            tv1.index = (tv1.index + 1) & TVR_MASK;
        } else {
            break;
        }
    }
}

//long TimerMng::add_timer(long expires, long cycle, long id, long tag)
void add_timer(long expires, long id, long tag)
{
    timer_list* timer = (timer_list*)calloc(1, sizeof(timer_list));
    if( timer ) {
        count++;
        //expires = ( expires + TIMER_TICK - 1 ) / TIMER_TICK;
        //if (expires < 1) expires = 1;
        //long nframe = timer_jiffies + expires;
        //timer->expires = nframe;


        //printf( "add_timer, id=%d, expires=%d, gMsec=%d, this=%d, jiffies=%d, start=%d\n", id, expires, gMsec, timer->expires, timer_jiffies, gStartMsec );
        timer->id = id;
        timer->tag = tag;
        timer->owner = 0;

        timer->expires = frame( expires + gMsec + TIMER_TICK - 1 );
        QuePut(&gQueTimerPut, &timer->link);
        __sync_fetch_and_add( &gTmNum, 1 );
    }
}


void action(unsigned long curMsec)
{
    struct list_head quePut;
    struct list_head *pos;
    timer_list *timer;

    INIT_LIST_HEAD(&quePut);
    if (QueTryAll(&gQueTimerPut, &quePut)) {
        while (!LIST_EMPTY(&quePut)) {
            pos = quePut.next;
            LIST_DEL_INIT(pos);
            timer = LIST_ENTRY(pos, timer_list, link);
            internal_add_timer( timer );
        }
    }
    run_timer_list(curMsec);
}

void* timerThread(void *param)
{
    prctl(PR_SET_NAME, "timer");
    while (gOn) {
        if (!gTimeControl) {
            action(gMsec);
        }
        usleep(TIMER_TICK*1000);
    }
    return NULL;
}


void start_timer()
{
    QueInit(&gQueTimerPut);
    for (int i = 0; i < MAX_LUA_THREAD_NUM; ++i) {
        QueInit(gQueTimerGet + i);
    }
    initTimer();

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,timerThread, NULL);
    pthread_attr_destroy(&attr);
}


int recv_timerq(struct list_head *q, int owner)
{
    return QueTryAll(gQueTimerGet + owner, q);
}


int timer_time_set_start(unsigned int curSec)
{
    printf("time_step, set_start, %d\n", curSec );
    gStartSec = curSec;
    gStartMsec = 0;
    timer_jiffies = 0;
    tv1.index = 0;
    tv2.index = 0;
    tv3.index = 0;
    tv4.index = 0;
    tv5.index = 0;
    return 0;
}


int timer_time_step(unsigned int curSec)
{
    static unsigned int last = 0;
    if ( curSec > last ) {
        unsigned int msec = (curSec - gStartSec) * 1000;
        printf("time_step, time_step, cur,%d, pre,%d, frame,%ld\n", curSec, last, frame( msec ));
        if (msec > 0) {
            //printf( "timer_time_step, start, curSec=%d, last=%d, offset=%d\n", curSec, last, curSec - last );
            action(msec);
            //printf( "timer_time_step, over\n" );
            return 0;
        }
        last = curSec;
    }
    return -1;
}
