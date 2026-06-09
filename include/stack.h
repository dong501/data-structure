#ifndef STACK_H
#define STACK_H

#include "patient.h"

/* ─── 처리 이력 스택 (LIFO) ─── */
typedef struct {
    Patient data[MAX_STACK];
    int     top;
} Stack;

void    stack_init    (Stack *s);
int     stack_is_empty(const Stack *s);
int     stack_is_full (const Stack *s);
int     stack_push    (Stack *s, Patient p);   /* 0: 성공, -1: 가득 참 */
int     stack_pop     (Stack *s, Patient *out);/* 0: 성공, -1: 비어있음 */
int     stack_peek    (const Stack *s, Patient *out);
void    stack_print   (const Stack *s);

#endif /* STACK_H */
