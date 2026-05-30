#define SYSTICK_BASE 0xE000E010
#define CPU_CLOCK_HZ 25000000

#define IVT_ARRAY_SIZE (16U)

// STCSR - Control and Status Register
//          This configures the SysTick clock, enables the SysTick interrupt,
//          and indicates the counter status
// STRVR - Reload Value Register
//          This provides the wrap value for the counter
// STCVR - Current Value Register
// STCR  - Calibration Value Register
//          This indicates the preload value required for a 10ms (100Hz) system clock.
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_Registers;

#define SysTick ((SysTick_Registers*)SYSTICK_BASE)
