#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "patient.h"

/* ─── 최대 힙 기반 우선순위 큐 ─── */
typedef struct {
    Patient heap[MAX_PATIENTS + 1]; /* 1-indexed */
    int     size;
} PriorityQueue;

void    pq_init   (PriorityQueue *pq);
int     pq_is_empty(const PriorityQueue *pq);
int     pq_is_full (const PriorityQueue *pq);
int     pq_push   (PriorityQueue *pq, Patient p);   /* 0: 성공, -1: 포화 */
int     pq_pop    (PriorityQueue *pq, Patient *out); /* 0: 성공, -1: 공백 */
void    pq_print  (const PriorityQueue *pq);
void    pq_sort   (PriorityQueue *pq);               /* 힙 재정렬 */

/* 우선순위 비교: effective_priority 낮을수록 높은 우선순위,
   같으면 id(접수 순) 낮을수록 우선 */
int     pq_compare(const Patient *a, const Patient *b); /* a가 b보다 우선이면 >0 */

#endif /* PRIORITY_QUEUE_H */
