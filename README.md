# 🏥 응급실 대기열 관리 시스템

## 프로젝트 소개
응급실에 방문하는 환자들을 중증도와 방문 순서에 따라 효율적으로 관리하는
**콘솔 기반 진료 안내 시스템**입니다.

## 팀 정보
| 항목 | 내용 |
|------|------|
| 팀명 | 극동아시아타이거즈 |
| 팀원 | 동현우, 이성재 |
| 과목 | 자료구조 |
| 언어 | C |

## 팀원 역할
| 팀원 | 담당 |
|------|------|
| 동현우 | 원형큐, 큐 정렬(MaxHeap), 에이징 알고리즘 |
| 이성재 | 디큐, 스택(처리 이력/취소), 콘솔 UI |
| 공통 | GitHub 세팅, README 작성 |

## 사용 자료구조
| 자료구조 | 역할 |
|----------|------|
| 원형 큐 (Circular Queue) | 일반 환자 대기열 관리 |
| 최대 힙 우선순위 큐 (Max-Heap Priority Queue) | 응급 환자 중증도 기반 정렬 처리 |
| 스택 (Stack) | 최근 처리 이력 저장 및 Undo(취소) |

## 개발 환경
- Language: C (C99)
- Compiler: GCC
- OS: Windows / Linux / macOS
- IDE: Visual Studio Code

## 프로젝트 구조
```
emergency_queue/
├── src/
│   ├── main.c             # 메인 진입점
│   ├── patient.c          # 환자 구조체 유틸
│   ├── circular_queue.c   # 원형 큐 구현
│   ├── priority_queue.c   # 최대 힙 우선순위 큐 구현
│   ├── stack.c            # 스택 구현
│   └── ui.c               # 콘솔 UI 및 기능 핸들러
├── include/
│   ├── patient.h
│   ├── circular_queue.h
│   ├── priority_queue.h
│   ├── stack.h
│   └── ui.h
├── data/                  # 테스트 데이터 (추후 사용)
├── docs/                  # 발표 자료
├── Makefile
└── README.md
```

## 실행 방법

### Linux / macOS
```bash
make
./emergency_queue
```

### Windows (GCC)
```bash
gcc -Wall -Iinclude -o emergency_queue src/main.c src/patient.c src/circular_queue.c src/priority_queue.c src/stack.c src/ui.c
emergency_queue.exe
```

## 주요 기능

### 1. 일반 환자 접수 (원형 큐)
일반 환자를 원형 큐에 등록합니다. 대기열이 가득 차면 접수를 거부합니다.

### 2. 응급 환자 접수 (우선순위 큐)
응급 환자를 최대 힙 기반 우선순위 큐에 등록합니다.
같은 중증도이면 먼저 온 환자가 우선 처리됩니다.

### 3. 다음 환자 진료
응급 대기열을 먼저 처리하고, 없으면 일반 대기열에서 처리합니다.

### 4. 처리 취소 (Undo)
가장 최근에 처리된 환자를 스택에서 꺼내 원래 대기열로 복구합니다.

### 5. 에이징 (Aging)
오래 기다린 환자의 우선순위를 자동으로 높여 무한 대기를 방지합니다.
3턴마다 `effective_priority`가 1씩 감소합니다.

## 중증도 기준 (KTAS 기반 단순화)
| 등급 | 분류 | 예시 |
|------|------|------|
| 1 | 즉시처치 (CRITICAL) | 심정지, 의식불명 |
| 2 | 응급 (EMERGENCY) | 호흡곤란, 심한 출혈 |
| 3 | 긴급 (URGENT) | 고열, 골절 |
| 4 | 준긴급 (SEMI-URGENT) | 경미한 부상 |
| 5 | 비응급 (NON-URGENT) | 단순 감기 |

## 어려웠던 점
- 최대 힙 정렬 기준을 `effective_priority`와 접수 순서(id) 두 가지로 구현
- 에이징 후 힙 재정렬 처리 (Floyd 알고리즘 적용)
- 원형 큐의 front/rear 포화 판정 로직

## 느낀 점
각 자료구조가 어떤 상황에 적합한지 직접 구현하면서 체득할 수 있었습니다.
