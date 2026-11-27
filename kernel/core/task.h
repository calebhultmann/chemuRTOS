#include <stdint.h>

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SUSPENDED
} TaskState;

typedef struct TCB {
    volatile uint32_t* stackPointer;
    volatile TaskState state;
    uint8_t priority;
    uint32_t wakeUpTick;
    uint32_t* stackBase;
    uint32_t stackSize;
    const char* name;
    struct TCB* next;
} TCB_t;