#ifndef UI_H
#define UI_H

#include "circular_queue.h"
#include "priority_queue.h"
#include "stack.h"

void ui_clear_screen(void);
void ui_draw_header(void);
void ui_draw_separator(void);
void ui_main_menu(void);

/* 기능별 핸들러 */
void ui_enqueue_normal  (CircularQueue *cq, PriorityQueue *pq, int *id_counter);
void ui_enqueue_emergency(PriorityQueue *pq, int *id_counter);
void ui_dequeue_next    (CircularQueue *cq, PriorityQueue *pq, Stack *hist);
void ui_cancel_last     (CircularQueue *cq, PriorityQueue *pq, Stack *hist);
void ui_show_queue      (const CircularQueue *cq, const PriorityQueue *pq);
void ui_show_history    (const Stack *hist);
void ui_run_aging       (CircularQueue *cq, PriorityQueue *pq);

#endif /* UI_H */
