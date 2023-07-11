#include <sys/time.h>
#include "que.h"

void QueInit(Que *q)
{
    INIT_LIST_HEAD( &q->chain );
    pthread_mutex_init( &q->mut, NULL );
    //pthread_cond_init(&q->cond, NULL);

    pthread_condattr_init( &q->condattr );
    pthread_condattr_setclock( &q->condattr, CLOCK_MONOTONIC );
    pthread_cond_init( &q->cond, &q->condattr );
    q->wait = 0;
}

struct list_head* QueGet(Que *q)
{
    struct list_head *pos = NULL;
    pthread_mutex_lock( &q->mut );
    while ( LIST_EMPTY( &q->chain ) ) {
        q->wait += 1;
        pthread_cond_wait( &q->cond, &q->mut );
        q->wait -= 1;
    }
    pos = q->chain.next;
    LIST_DEL( pos );
    pthread_mutex_unlock( &q->mut );
    return pos;
}

int QueGetAll(Que *q, struct list_head *head)
{
    int has = 0;
    pthread_mutex_lock(&q->mut);
    while (LIST_EMPTY(&q->chain)) {
        q->wait += 1;
        pthread_cond_wait(&q->cond, &q->mut);
        q->wait -= 1;
    }
    if ( !LIST_EMPTY( &q->chain ) ) {
        LIST_SPLICE_TAIL( &q->chain, head );
        INIT_LIST_HEAD( &q->chain );
        has = 1;
    }
    pthread_mutex_unlock( &q->mut );
    return has;
}


int QueGetAllTimeWait( Que *q, struct list_head *head, int msec )
{
    int has, rc;
    struct timespec ts;

    clock_gettime( CLOCK_MONOTONIC, &ts );
    ts.tv_nsec += ( msec * 1000000 );
    if ( ts.tv_nsec >= 1000000000 ) {
        ts.tv_sec += 1;
        ts.tv_nsec -= 1000000000;
    }

    has = 0;
    rc = 0;

    pthread_mutex_lock( &q->mut );
    while ( LIST_EMPTY( &q->chain ) && rc == 0 ) {
        q->wait += 1;
        rc = pthread_cond_timedwait( &q->cond, &q->mut, &ts );
        q->wait -= 1;
    }

    if ( !LIST_EMPTY(&q->chain) ) {
        LIST_SPLICE_TAIL( &q->chain, head );
        INIT_LIST_HEAD( &q->chain );
        has = 1;
    }
    pthread_mutex_unlock(&q->mut);
    return has;
}


int QuePut( Que *q, struct list_head *it )
{
    int sig = 0, empty = 0;
    pthread_mutex_lock( &q->mut );
    if ( LIST_EMPTY( &q->chain ) ) empty = 1;
    LIST_ADD_TAIL( it, &q->chain );
    sig = q->wait;
    pthread_mutex_unlock( &q->mut );
    if ( sig ) pthread_cond_signal( &q->cond );
    return empty;
}

int QuePutHead( Que *q, struct list_head *it )
{
    int sig = 0, empty = 0;
    pthread_mutex_lock( &q->mut );
    if ( LIST_EMPTY( &q->chain ) ) empty = 1;
    LIST_ADD( it, &q->chain );
    sig = q->wait;
    pthread_mutex_unlock( &q->mut );
    if ( sig ) pthread_cond_signal( &q->cond );
    return empty;
}


int QuePutAll( Que *q, struct list_head *it )
{
    int sig = 0, empty = 0;
    pthread_mutex_lock( &q->mut );
    if ( LIST_EMPTY( &q->chain ) ) empty = 1;
    LIST_SPLICE_TAIL( it, &q->chain );
    sig = q->wait;
    pthread_mutex_unlock( &q->mut );
    if ( sig ) pthread_cond_signal( &q->cond );
    return empty;
}


struct list_head* QueTry(Que *q)
{
    if ( LIST_EMPTY( &q->chain ) ) return NULL;

    struct list_head *pos = NULL;
    pthread_mutex_lock( &q->mut );
    if (!LIST_EMPTY( &q->chain ) ) {
        pos = q->chain.next;
        LIST_DEL( pos );
    }
    pthread_mutex_unlock( &q->mut );
    return pos;
}

int QueTryAll( Que *q, struct list_head *head )
{
    int flag;
    if ( LIST_EMPTY( &q->chain ) ) return 0;

    flag = 0;
    pthread_mutex_lock( &q->mut );
    if ( !LIST_EMPTY( &q->chain ) ) {
        LIST_SPLICE_TAIL( &q->chain, head );
        INIT_LIST_HEAD( &q->chain );
        flag = 1;
    }
    pthread_mutex_unlock( &q->mut );
    return flag;
}

int QuePeek(Que *q)
{
    if ( LIST_EMPTY( &q->chain ) ) return 0;
    return 1;
}

int QueWake(Que *q)
{
    if (q->wait) {
        pthread_cond_signal(&q->cond);
        return 1;
    }
    return 0;
}
