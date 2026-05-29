TARGET := chemuRTOS

CC := arm-none-eabi-gcc
OBJDUMP := arm-none-eabi-objdump
NM := arm-none-eabi-nm

CFLAGS := \
	-g \
	-mcpu=cortex-m3 \
	-mthumb \
	-std=c11 \
	-O0

LDFLAGS := \
	-mcpu=cortex-m3 \
	-mthumb \
	--specs=nano.specs \
	-nostartfiles \
	-T mps2-an385.ld \
	-Wl,-Map=build/$(TARGET).map

BUILD_DIR := build

C_SOURCES := \
	startup_mps2-an385.c \
	main.c

C_OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

QEMU := qemu-system-arm

QEMU_MACHINE := mps2-an385

QEMU_FLAGS := \
	-M $(QEMU_MACHINE) \
	-cpu cortex-m3 \
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