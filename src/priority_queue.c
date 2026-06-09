#include <stdio.h>
#include "priority_queue.h"

/* ── 초기화 ── */
void pq_init(PriorityQueue *pq)  { pq->size = 0; }
int  pq_is_empty(const PriorityQueue *pq) { return pq->size == 0; }
int  pq_is_full (const PriorityQueue *pq) { return pq->size >= MAX_PATIENTS; }

/* ── 비교: a가 b보다 높은 우선순위면 양수 반환
   effective_priority 낮을수록 우선, 같으면 id 낮을수록 우선 ── */
int pq_compare(const Patient *a, const Patient *b)
{
    if (a->effective_priority != b->effective_priority)
        return b->effective_priority - a->effective_priority; /* 낮을수록 우선 */
    return b->id - a->id;  /* id 낮을수록 (먼저 온 환자) 우선 */
}

/* ── 내부 헬퍼 ── */
static void swap(Patient *a, Patient *b)
{
    Patient tmp = *a; *a = *b; *b = tmp;
}

static void sift_up(PriorityQueue *pq, int i)
{
    while (i > 1) {
        int parent = i / 2;
        if (pq_compare(&pq->heap[i], &pq->heap[parent]) > 0) {
            swap(&pq->heap[i], &pq->heap[parent]);
            i = parent;
        } else break;
    }
}

static void sift_down(PriorityQueue *pq, int i)
{
    int n = pq->size;
    while (1) {
        int largest = i;
        int l = 2 * i, r = 2 * i + 1;
        if (l <= n && pq_compare(&pq->heap[l], &pq->heap[largest]) > 0) largest = l;
        if (r <= n && pq_compare(&pq->heap[r], &pq->heap[largest]) > 0) largest = r;
        if (largest == i) break;
        swap(&pq->heap[i], &pq->heap[largest]);
        i = largest;
    }
}

/* ── 삽입 ── */
int pq_push(PriorityQueue *pq, Patient p)
{
    if (pq_is_full(pq)) return -1;
    pq->heap[++pq->size] = p;
    sift_up(pq, pq->size);
    return 0;
}

/* ── 최우선 환자 꺼내기 ── */
int pq_pop(PriorityQueue *pq, Patient *out)
{
    if (pq_is_empty(pq)) return -1;
    *out = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size--];
    sift_down(pq, 1);
    return 0;
}

/* ── 힙 재정렬 (에이징 후 우선순위 변경 시 사용) ── */
void pq_sort(PriorityQueue *pq)
{
    /* Floyd의 힙 구성 알고리즘으로 전체 재정렬 */
    for (int i = pq->size / 2; i >= 1; i--)
        sift_down(pq, i);
}

/* ── 출력 ── */
void pq_print(const PriorityQueue *pq)
{
    if (pq_is_empty(pq)) {
        printf("  (응급 대기열이 비어 있습니다)\n");
        return;
    }
    printf("  응급 대기열 (%d명, 우선순위 순):\n", pq->size);
    /* 정렬된 순서로 출력하기 위해 임시 복사 후 반복 pop */
    PriorityQueue tmp = *pq;
    Patient p;
    while (!pq_is_empty(&tmp)) {
        pq_pop(&tmp, &p);
        print_patient(&p);
    }
}
