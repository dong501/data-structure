#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "ui.h"

/* ANSI 색상 */
#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31;1m"
#define COLOR_ORANGE  "\x1b[38;5;208m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_CYAN    "\x1b[36m"

/* 함수 구현 */
static void delay_ms(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

static const char* get_severity_color(int severity) {
    switch (severity) {
        case 1: return COLOR_RED; case 2: return COLOR_ORANGE;
        case 3: return COLOR_YELLOW; case 4: return COLOR_GREEN;
        case 5: return COLOR_BLUE; default: return COLOR_RESET;
    }
}

static int get_utf8_visual_width(const char *str) {
    int width = 0;
    while (*str) {
        if ((*str & 0x80) == 0) { width += 1; str++; }
        else if ((*str & 0xE0) == 0xC0) { width += 2; str += 2; }
        else if ((*str & 0xF0) == 0xE0) { width += 2; str += 3; }
        else { width += 2; str += 4; }
    }
    return width;
}

static void print_patient_cards(Patient* arr, int count, const char* title, const char* title_color) {
    printf("  %s[%s - 총 %d명]%s\n", title_color, title, count, COLOR_RESET);
    if (count == 0) { printf("  (대기 중인 환자가 없습니다)\n\n"); return; }
    for (int i = 0; i < count; i += 4) {
        int row = (count - i > 4) ? 4 : (count - i);
        printf("  "); for (int j = 0; j < row; j++) printf("%s┌────────────────┐%s  ", get_severity_color(arr[i+j].severity), COLOR_RESET); printf("\n");
        printf("  "); for (int j = 0; j < row; j++) {
            const char* c = get_severity_color(arr[i+j].severity);
            int p = 14 - get_utf8_visual_width(arr[i+j].name);
            printf("%s│%s %s%*s %s│%s  ", c, COLOR_RESET, arr[i+j].name, p < 0 ? 0 : p, "", c, COLOR_RESET);
        } printf("\n");
        printf("  "); for (int j = 0; j < row; j++) printf("%s│%s 중증도: %d      %s│%s  ", get_severity_color(arr[i+j].severity), COLOR_RESET, arr[i+j].severity, get_severity_color(arr[i+j].severity), COLOR_RESET); printf("\n");
        printf("  "); for (int j = 0; j < row; j++) printf("%s│%s   [|____|]~    %s│%s  ", get_severity_color(arr[i+j].severity), COLOR_RESET, get_severity_color(arr[i+j].severity), COLOR_RESET); printf("\n");
        printf("  "); for (int j = 0; j < row; j++) printf("%s└────────────────┘%s  ", get_severity_color(arr[i+j].severity), COLOR_RESET); printf("\n\n");
    }
}

void ui_clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ui_draw_header(void) {
    printf("\n  %s╔══════════════════════════════════════════════════╗\n", COLOR_CYAN);
    printf("  ║      🏥  응급실 대기열 관리 시스템              ║\n");
    printf("  ╚══════════════════════════════════════════════════╝%s\n", COLOR_RESET);
}

void ui_draw_separator(void) { printf("  --------------------------------------------------\n"); }

void ui_main_menu(void) {
    printf("\n");
    // 상단 테두리 (가로선만 사용하여 깔끔하게)
    printf("  %s══════════════════════════════════════════════════%s\n", COLOR_CYAN, COLOR_RESET);
    printf("                 %s[ 시 스 템  메 뉴 ]%s\n", COLOR_YELLOW, COLOR_RESET);
    printf("  %s══════════════════════════════════════════════════%s\n\n", COLOR_CYAN, COLOR_RESET);
    
    // 메뉴 항목 (이모지와 색상 포인트 적용)
    printf("    %s[%s1%s]%s 🏥 일반 환자 접수   %s(원형큐)%s\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET, COLOR_BLUE, COLOR_RESET);
    printf("    %s[%s2%s]%s 🚑 응급 환자 접수   %s(우선순위큐)%s\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET, COLOR_RED, COLOR_RESET);
    printf("    %s[%s3%s]%s 🩺 다음 환자 진료   %s(Dequeue)%s\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET, COLOR_YELLOW, COLOR_RESET);
    printf("    %s[%s4%s]%s ⏪ 마지막 처리 취소 %s(Undo/Stack)%s\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET, COLOR_ORANGE, COLOR_RESET);
    printf("    %s[%s5%s]%s 📊 현재 대기열 조회\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET);
    printf("    %s[%s6%s]%s 📋 처리 이력 조회\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET);
    printf("    %s[%s7%s]%s ⏳ 에이징 실행      %s(수동)%s\n\n", COLOR_CYAN, COLOR_GREEN, COLOR_CYAN, COLOR_RESET, COLOR_CYAN, COLOR_RESET);
    
    // 종료 메뉴는 시각적으로 분리
    printf("    %s[%s0%s]%s 🚪 프로그램 종료\n", COLOR_CYAN, COLOR_RED, COLOR_CYAN, COLOR_RESET);
    printf("  %s--------------------------------------------------%s\n", COLOR_CYAN, COLOR_RESET);
    
    // 입력 프롬프트 강조
    printf("  %s▶ 원하시는 메뉴 번호를 입력하세요 >%s ", COLOR_YELLOW, COLOR_RESET);
}
// ▼ 사라졌던 함수! ui_enqueue_normal 바로 위에 붙여넣으세요.
static Severity input_severity(int is_emergency) {
    int choice;
    if (is_emergency) {
        printf("    %s1) 즉시처치 (CRITICAL)%s\n    %s2) 응급     (EMERGENCY)%s\n  선택 (1~2) > ", COLOR_RED, COLOR_RESET, COLOR_ORANGE, COLOR_RESET);
        scanf("%d", &choice); getchar();
        return (choice == 1) ? 1 : 2;
    } else {
        printf("    %s3) 긴급     (URGENT)%s\n    %s4) 준긴급   (SEMI-URGENT)%s\n    %s5) 비응급   (NON-URGENT)%s\n  선택 (3~5) > ", COLOR_YELLOW, COLOR_RESET, COLOR_GREEN, COLOR_RESET, COLOR_BLUE, COLOR_RESET);
        scanf("%d", &choice); getchar();
        if (choice < 3 || choice > 5) return 5;
        return (Severity)choice;
    }
}

void ui_enqueue_normal(CircularQueue *cq, PriorityQueue *pq, int *id_counter) {
    (void)pq; Patient p; memset(&p, 0, sizeof(Patient));
    p.id = (*id_counter)++; printf("  이름: "); fgets(p.name, NAME_LEN, stdin); p.name[strcspn(p.name, "\n")] = 0;
    p.severity = input_severity(0); p.effective_priority = (int)p.severity;
    cq_enqueue(cq, p);
}

void ui_enqueue_emergency(PriorityQueue *pq, int *id_counter) {
    Patient p; memset(&p, 0, sizeof(Patient));
    p.id = (*id_counter)++; printf("  이름: "); fgets(p.name, NAME_LEN, stdin); p.name[strcspn(p.name, "\n")] = 0;
    p.severity = input_severity(1); p.effective_priority = (int)p.severity;
    pq_push(pq, p);
}

void ui_dequeue_next(CircularQueue *cq, PriorityQueue *pq, Stack *hist) {
    ui_draw_separator(); Patient served;
    if (!pq_is_empty(pq)) { pq_pop(pq, &served); printf("  🚨 응급 환자 호출:\n"); }
    else if (!cq_is_empty(cq)) { cq_dequeue(cq, &served); printf("  🏥 일반 환자 호출:\n"); }
    else { printf("  ℹ️  대기 중인 환자가 없습니다.\n"); return; }
    print_patient(&served);
    printf("\n  진료 준비 중...\n  ");
    for (int i = 1; i <= 10; i++) { printf("\r  [%s■%s%*s] %d%%", COLOR_CYAN, COLOR_RESET, i, "", 10 - i, i * 10); fflush(stdout); delay_ms(100); }
    printf("\n\n"); stack_push(hist, served); printf("  → 진료 완료.\n");
}

void ui_cancel_last(CircularQueue *cq, PriorityQueue *pq, Stack *hist) {
    ui_draw_separator(); Patient p;
    if (stack_pop(hist, &p) < 0) { printf("  ℹ️  이력 없음.\n"); return; }
    printf("  복구 완료.\n");
    if (p.severity <= 2) pq_push(pq, p); else cq_enqueue(cq, p);
}

void ui_show_queue(const CircularQueue *cq, const PriorityQueue *pq) {
    ui_draw_separator();
    printf("  %s[시스템 상태: NORMAL] | 총 대기: %d명%s\n\n", COLOR_CYAN, pq->size + cq->size, COLOR_RESET);
    PriorityQueue tmp = *pq; Patient pq_arr[MAX_PATIENTS]; int pq_count = 0;
    while (!pq_is_empty(&tmp)) pq_pop(&tmp, &pq_arr[pq_count++]);
    print_patient_cards(pq_arr, pq_count, "🚨 응급 대기열", COLOR_RED);
    Patient cq_arr[MAX_PATIENTS]; int cq_count = cq->size;
    for (int i = 0; i < cq_count; i++) cq_arr[i] = cq->data[(cq->front + i) % MAX_PATIENTS];
    print_patient_cards(cq_arr, cq_count, "🏥 일반 대기열", COLOR_GREEN);
    fflush(stdout);
}

void ui_show_history(const Stack *hist) { ui_draw_separator(); stack_print(hist); }

void ui_run_aging(CircularQueue *cq, PriorityQueue *pq) {
    // 1. 일반 환자 에이징 (위에서 수정한 cq_aging 호출)
    cq_aging(cq);
    
    // 2. 응급 환자 에이징
    for (int i = 1; i <= pq->size; i++) {
        pq->heap[i].wait_turns++;
        
        /* 다시 3턴마다 바뀌도록 % 3 으로 원복! */
        if (pq->heap[i].wait_turns % 3 == 0 && pq->heap[i].effective_priority > 1) {
            
            pq->heap[i].effective_priority--;
            
            /* 화면 색상/숫자 동기화 유지 */
            pq->heap[i].severity = pq->heap[i].effective_priority; 
            
            printf("  [응급 에이징] #%03d %s: 우선순위 상향! (현재 중증도: %d)\n",
                   pq->heap[i].id, pq->heap[i].name, pq->heap[i].effective_priority);
        }
    }
    
    // 우선순위가 변동되었으므로 힙 정렬 갱신
    if (pq->size > 0) pq_sort(pq);
}