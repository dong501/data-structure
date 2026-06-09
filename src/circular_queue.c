#include <stdio.h>
#include "circular_queue.h"

/* ── 초기화 ── */
void cq_init(CircularQueue *q)
{
    q->front = 0;
    q->rear  = 0;
    q->size  = 0;
}

int cq_is_full(const CircularQueue *q)  { return q->size == MAX_PATIENTS; }
int cq_is_empty(const CircularQueue *q) { return q->size == 0; }

/* ── 삽입 (일반 접수) ── */
int cq_enqueue(CircularQueue *q, Patient p)
{
    if (cq_is_full(q)) return -1;
    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % MAX_PATIENTS;
    q->size++;
    return 0;
}

/* ── 제거 (가장 오래 대기한 환자) ── */
int cq_dequeue(CircularQueue *q, Patient *out)
{
    if (cq_is_empty(q)) return -1;
    *out = q->data[q->front];
    q->front = (q->front + 1) % MAX_PATIENTS;
    q->size--;
    return 0;
}

/* ── 대기열 출력 ── */
void cq_print(const CircularQueue *q)
{
    if (cq_is_empty(q)) {
        printf("  (일반 대기열이 비어 있습니다)\n");
        return;
    }
    printf("  일반 대기열 (%d명):\n", q->size);
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % MAX_PATIENTS;
        print_patient(&q->data[idx]);
    }
}

/* ── 에이징: 대기 턴마다 effective_priority를 1씩 감소(우선순위 증가) ── */
void cq_aging(CircularQueue *q)
{
    for (int i = 0; i < q->size; i++) {
        int idx = (q->front + i) % MAX_PATIENTS;
        q->data[idx].wait_turns++;
        
        /* 다시 3턴마다 바뀌도록 % 3 으로 원복! */
        if (q->data[idx].wait_turns % 3 == 0 &&
            q->data[idx].effective_priority > 1) {
            
            q->data[idx].effective_priority--;
            
            /* 화면 색상/숫자 동기화 유지 */
            q->data[idx].severity = q->data[idx].effective_priority; 
            
            printf("  [일반 에이징] #%03d %s: 우선순위 상향! (현재 중증도: %d)\n",
                   q->data[idx].id,
                   q->data[idx].name,
                   q->data[idx].effective_priority);
        }
    }
}