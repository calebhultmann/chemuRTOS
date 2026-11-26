volatile int dummy_data = 1;  // forces a .data symbol
volatile int dummy_bss;       // forces a .bss symbol

int main(void) {
    return 0;
}