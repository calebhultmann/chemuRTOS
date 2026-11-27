#include "kernel.h"

#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "task.h"

static uint32_t taskStacks[MAX_TASKS][STACK_SIZE_WORDS];

static TCB_t tcbPool[MAX_TASKS];
static bool  tcbUsed[MAX_TASKS];

// should take a function pointer arg? for the actual task to do
uint32_t create_task(void (*entry)(void *), void *args, const char *name) {
    (void) entry;
    (void) args;
    (void) name;

    (void) tcbPool;
    (void) tcbUsed;
    (void) taskStacks;

    // Set up TCB struct w/ stack
    // Set up exception frame in stack
    // set task state to ready
    // Add to task list
    // return task id? (Is this needed?)
    return -1;
}