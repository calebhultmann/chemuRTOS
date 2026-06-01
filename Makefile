TARGET := chemuRTOS

CC := arm-none-eabi-gcc
OBJDUMP := arm-none-eabi-objdump
NM := arm-none-eabi-nm


# ---BOARD---
BOARD ?= mps2-an385
BOARD_DIR := board/$(BOARD)
BOARD_SRC_FILES := \
	$(BOARD_DIR)/init.c \
	$(BOARD_DIR)/vectors.c \


# ---ARCHITECTURE---
ARCH_mps2-an385 := cortex-m3
ARCH := $(ARCH_$(BOARD))
ARCH_DIR := arch/$(ARCH)
ARCH_SRC_FILES := \
	$(ARCH_DIR)/exception.c \
	$(ARCH_DIR)/startup.c


#---KERNEL---
KERNEL_DIR := kernel
KERNEL_SRC_FILES := \
	kernel/core/scheduler.c \
	kernel/core/task.c


#---COMPILER---
CFLAGS_cortex-m3 := -mcpu=cortex-m3 -mthumb
CFLAGS := \
	-g \
	-std=c11 \
	-O0
CFLAGS += $(CFLAGS_$(ARCH))
CFLAGS += -Iarch/$(ARCH) -Iboard/$(BOARD)

#---LINKER---
LDFLAGS_cortex-m3 := -mcpu=cortex-m3 -mthumb
LDSCRIPT := $(BOARD_DIR)/linker.ld
LDFLAGS := \
	--specs=nano.specs \
	-nostartfiles \
	-T $(LDSCRIPT) \
	-Wl,-Map=build/$(TARGET).map

BUILD_DIR := build

C_SOURCES := \
	$(KERNEL_SRC_FILES) \
	$(BOARD_SRC_FILES) \
	$(ARCH_SRC_FILES) \
	main.c

C_OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

QEMU := qemu-system-arm

QEMU_MACHINE := $(BOARD)

QEMU_FLAGS := \
	-M $(QEMU_MACHINE) \
	-cpu $(ARCH) \
	-kernel build/$(TARGET).elf \
	-nographic \
	-S \
	-gdb tcp::3333 \
	-no-reboot \
	-no-shutdown

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BUILD_DIR)/$(TARGET).elf
	$(QEMU) $(QEMU_FLAGS)

dump: $(BUILD_DIR)/$(TARGET).elf
	$(OBJDUMP) -D $<

sections: $(BUILD_DIR)/$(TARGET).elf
	$(OBJDUMP) -h $<

symbols: $(BUILD_DIR)/$(TARGET).elf
	$(NM) $<

clean:
	rm -rf build