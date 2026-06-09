#include <stdio.h>
#include "stack.h"

void stack_init(Stack *s)          { s->top = -1; }
int  stack_is_empty(const Stack *s){ return s->top < 0; }
int  stack_is_full (const Stack *s){ return s->top >= MAX_STACK - 1; }

int stack_push(Stack *s, Patient p)
{
    if (stack_is_full(s)) return -1;
    s->data[++s->top] = p;
    return 0;
}

int stack_pop(Stack *s, Patient *out)
{
    if (stack_is_empty(s)) return -1;
    *out = s->data[s->top--];
    return 0;
}

int stack_peek(const Stack *s, Patient *out)
{
    if (stack_is_empty(s)) return -1;
    *out = s->data[s->top];
    return 0;
}

void stack_print(const Stack *s)
{
    if (stack_is_empty(s)) {
        printf("  (처리 이력이 없습니다)\n");
        return;
    }
    printf("  처리 이력 (최근 순):\n");
    for (int i = s->top; i >= 0; i--)
        print_patient(&s->data[i]);
}
