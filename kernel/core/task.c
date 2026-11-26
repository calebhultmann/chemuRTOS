#include <stdint.h>
#include <stdbool.h>
#include "../config.h"

static uint32_t taskStacks[MAX_TASKS][STACK_SIZE_WORDS];

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

static TCB_t tcbPool[MAX_TASKS];
static bool  tcbUsed[MAX_TASKS];

// should take a function pointer arg? for the actual task to do
int create_task(void) {
    (void) tcbPool;
    (void) tcbUsed;
    (void) taskStacks;

    // Set up TCB struct w/ stack
    // Set up exception frame in stack
    // set task state to ready
    // Add to task list
    // return task id? (Is this needed?)
    return 0;
}