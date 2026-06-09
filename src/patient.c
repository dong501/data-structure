#include <stdio.h>
#include "patient.h"

const char *severity_str(Severity s)
{
    switch (s) {
        case LEVEL_CRITICAL:  return "1-즉시처치";
        case LEVEL_EMERGENCY: return "2-응  급";
        case LEVEL_URGENT:    return "3-긴  급";
        case LEVEL_SEMI:      return "4-준긴급";
        case LEVEL_NON:       return "5-비응급";
        default:              return "알수없음";
    }
}

void print_patient(const Patient *p)
{
    printf("  [#%03d] %-12s | 중증도: %s | 유효우선순위: %d | 대기턴: %d\n",
           p->id, p->name, severity_str(p->severity),
           p->effective_priority, p->wait_turns);
}
