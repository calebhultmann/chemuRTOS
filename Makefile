TARGET    := chemuRTOS
BUILD_DIR := build

CC      := arm-none-eabi-gcc
OBJDUMP := arm-none-eabi-objdump
NM      := arm-none-eabi-nm
SIZE    := arm-none-eabi-size
QEMU    := qemu-system-arm

# =============================================================================
# Board -> architecture mapping
#   Add a new board by adding one ARCH_<board> line and a board/<board>/ folder.
# =============================================================================
BOARD ?= mps2-an385

ARCH_mps2-an385 := cortex-m3
ARCH := $(ARCH_$(BOARD))
ifeq ($(ARCH),)
$(error Unknown BOARD '$(BOARD)': add an ARCH_$(BOARD) line to the Makefile)
endif

BOARD_DIR  := board/$(BOARD)
ARCH_DIR   := arch/$(ARCH)
KERNEL_DIR := kernel
API_DIR    := include

# =============================================================================
# Sources: every .c / .S in a layer's folder is compiled automatically,
# so a new file can't be silently left out of the build.
# =============================================================================
ARCH_SRCS   := $(wildcard $(ARCH_DIR)/*.c   $(ARCH_DIR)/*.S)
BOARD_SRCS  := $(wildcard $(BOARD_DIR)/*.c  $(BOARD_DIR)/*.S)
KERNEL_SRCS := $(wildcard $(KERNEL_DIR)/*/*.c)
APP_SRCS    := main.c

SRCS := $(ARCH_SRCS) $(BOARD_SRCS) $(KERNEL_SRCS) $(APP_SRCS)
OBJS := $(patsubst %,$(BUILD_DIR)/%.o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

# =============================================================================
# Per-layer include paths: this is what enforces the layering.
#   Every layer sees the public interfaces in include/.
#   Each layer additionally sees ONLY its own private headers.
#   So `#include "board.h"` from kernel code is a compile error, not a habit.
# =============================================================================
$(BUILD_DIR)/$(ARCH_DIR)/%.o:   LAYER_INC := -I$(ARCH_DIR)
$(BUILD_DIR)/$(BOARD_DIR)/%.o:  LAYER_INC := -I$(BOARD_DIR)
$(BUILD_DIR)/$(KERNEL_DIR)/%.o: LAYER_INC := -I$(KERNEL_DIR) -I$(KERNEL_DIR)/core
$(BUILD_DIR)/main.o:            LAYER_INC :=

# =============================================================================
# Flags
# =============================================================================
CPUFLAGS_cortex-m3 := -mcpu=cortex-m3 -mthumb
CPUFLAGS := $(CPUFLAGS_$(ARCH))

CFLAGS := $(CPUFLAGS) -std=c11 -g -O0 \
          -Wall -Wextra -ffreestanding \
          -MMD -MP                     # emit .d files so header edits trigger rebuilds
ASFLAGS := $(CPUFLAGS) -g -MMD -MP

LDSCRIPT := $(BOARD_DIR)/linker.ld
LDFLAGS  := $(CPUFLAGS) --specs=nano.specs -nostartfiles \
            -T $(LDSCRIPT) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# =============================================================================
# Build rules
# =============================================================================
ELF := $(BUILD_DIR)/$(TARGET).elf

.PHONY: all run debug dump sections symbols size clean

all: $(ELF)

$(ELF): $(OBJS) $(LDSCRIPT)
	$(CC) $(LDFLAGS) $(OBJS) -o $@
	@$(SIZE) $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(API_DIR) $(LAYER_INC) -c $< -o $@

# Capital .S = assembly run through the C preprocessor (#include, #define work)
$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -I$(API_DIR) $(LAYER_INC) -c $< -o $@

-include $(DEPS)

# =============================================================================
# QEMU
#   make run    - boot and print UART output to this terminal
#   make debug  - boot halted, waiting for GDB on :3333 (cortex-debug attach)
#   Quit QEMU with Ctrl-A then X.
# =============================================================================
QEMU_FLAGS := -M $(BOARD) -cpu $(ARCH) -kernel $(ELF) \
              -nographic -no-reboot -no-shutdown

run: $(ELF)
	$(QEMU) $(QEMU_FLAGS)

debug: $(ELF)
	$(QEMU) $(QEMU_FLAGS) -S -gdb tcp::3333

# =============================================================================
# Inspection
# =============================================================================
dump: $(ELF)
	$(OBJDUMP) -D $<

sections: $(ELF)
	$(OBJDUMP) -h $<

symbols: $(ELF)
	$(NM) -n $<

size: $(ELF)
	$(SIZE) $<

clean:
	rm -rf $(BUILD_DIR)
