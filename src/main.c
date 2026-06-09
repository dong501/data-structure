#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"
#include "priority_queue.h"
#include "stack.h"
#include "ui.h"

int main(void)
{
    system("chcp 65001 > nul");
    
    CircularQueue cq;
    PriorityQueue pq;
    Stack         history;
    int           id_counter = 1;

    cq_init   (&cq);
    pq_init   (&pq);
    stack_init(&history);

    while (1) {
        ui_clear_screen();
        ui_draw_header();
        
        // 메인 메뉴 상단에는 현재 큐 상태 출력
        ui_show_queue(&cq, &pq); 
        ui_main_menu();

        int choice;
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        getchar(); 

        ui_clear_screen();
        ui_draw_header();

        // 1. 선택한 작업과 에이징을 먼저 "처리" 합니다.
        switch (choice) {
            case 1: 
                ui_enqueue_normal(&cq, &pq, &id_counter); 
                ui_run_aging(&cq, &pq); // 자동 에이징
                break;
            case 2: 
                ui_enqueue_emergency(&pq, &id_counter);      
                ui_run_aging(&cq, &pq); // 자동 에이징
                break;
            case 3: 
                ui_dequeue_next(&cq, &pq, &history);    
                ui_run_aging(&cq, &pq); // 진료 후에도 턴이 지났으니 에이징
                break;
            case 4: ui_cancel_last(&cq, &pq, &history); break;
            case 5: printf("\n  화면을 새로고침합니다.\n"); break;
            case 6: ui_show_history(&history); break;
            case 7: ui_run_aging(&cq, &pq); break;
            case 0: return 0;
            default: printf("\n  ⚠️ 잘못된 입력입니다.\n");
        }

        // 2. 처리가 전부 끝난 후의 "최신 대기열 상태"를 여기서 출력합니다!
        ui_show_queue(&cq, &pq); 

        printf("\n  계속하려면 Enter를 누르세요...");
        getchar();
    }
    return 0;
}