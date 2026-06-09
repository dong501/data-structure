#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "patient.h"

/* ─── 원형 큐 구조체 ─── */
typedef struct {
    Patient data[MAX_PATIENTS];
    int     front;
    int     rear;
    int     size;
} CircularQueue;

void    cq_init   (CircularQueue *q);
int     cq_is_full(const CircularQueue *q);
int     cq_is_empty(const CircularQueue *q);
int     cq_enqueue(CircularQueue *q, Patient p);   /* 0: 성공, -1: 포화 */
int     cq_dequeue(CircularQueue *q, Patient *out); /* 0: 성공, -1: 공백 */
void    cq_print  (const CircularQueue *q);
void    cq_aging  (CircularQueue *q);              /* 대기 환자 우선순위 상향 */

#endif /* CIRCULAR_QUEUE_H */
