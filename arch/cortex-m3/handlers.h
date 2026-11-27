#ifndef CHEMU_HANDLERS_H
#define CHEMU_HANDLERS_H

void hard_fault_handler(void);
void systick_handler(void);
void default_handler(void);

void reset_handler(void);

#endif