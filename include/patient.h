#ifndef PATIENT_H
#define PATIENT_H

#define NAME_LEN     32
#define MAX_PATIENTS 20   /* 원형큐 최대 수용 인원 */
#define MAX_STACK    50   /* 스택 최대 용량 */

/* 중증도 등급 (낮을수록 위급) */
typedef enum {
    LEVEL_CRITICAL  = 1,  /* 즉시 처치 */
    LEVEL_EMERGENCY = 2,  /* 응급 */
    LEVEL_URGENT    = 3,  /* 긴급 */
    LEVEL_SEMI      = 4,  /* 준긴급 */
    LEVEL_NON       = 5   /* 비응급 */
} Severity;

typedef struct {
    int      id;                  /* 접수 번호 */
    char     name[NAME_LEN];      /* 환자 이름 */
    Severity severity;            /* 중증도 */
    int      wait_turns;          /* 대기 턴 수 (에이징용) */
    int      effective_priority;  /* 실제 우선순위 (severity - 에이징 보정) */
} Patient;

/* 유틸 */
const char *severity_str(Severity s);
void        print_patient(const Patient *p);

#endif /* PATIENT_H */
