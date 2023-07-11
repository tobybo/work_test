#ifndef _QUE_H_
#define _QUE_H_

#include <pthread.h>
#include "mylist.h"

typedef struct {
    struct list_head chain;
    pthread_mutex_t mut;
    pthread_cond_t cond;
    pthread_condattr_t condattr;
    int wait;
} Que;

void QueInit(Que *q);

int QuePut(Que *q, struct list_head *it);
int QuePutHead(Que *q, struct list_head *it);
int QuePutAll(Que *q, struct list_head *it);

struct list_head* QueGet(Que *q);
struct list_head* QueTry(Que *q);

int QueTryAll(Que *q, struct list_head *head);
int QueGetAll(Que *q, struct list_head *head);
int QueGetAllTimeWait(Que *q, struct list_head *head, int msec);
int QuePeek(Que *q);
int QueWake(Que *q);

#endif

