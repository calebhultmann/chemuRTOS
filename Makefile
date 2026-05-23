TARGET := chemuRTOS

CC := arm-none-eabi-gcc
OBJDUMP := arm-none-eabi-objdump
NM := arm-none-eabi-nm

CFLAGS := \
	-ffreestanding \
	-mcpu=cortex-m3 \
	-mthumb \
	-Wall \
	-Wextra \
	-ffunction-sections \
	-fdata-sections

LDFLAGS := \
	-nostdlib \
	-T link.ld \
	-Wl,-Map=build/$(TARGET).map

BUILD_DIR := build

C_SOURCES := \
	reset.c \
	app/main.c

ASM_SOURCES := \
	startup.s

C_OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES))
ASM_OBJECTS := $(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

dump: $(BUILD_DIR)/$(TARGET).elf
	$(OBJDUMP) -D $<

sections: $(BUILD_DIR)/$(TARGET).elf
	$(OBJDUMP) -h $<

symbols: $(BUILD_DIR)/$(TARGET).elf
	$(NM) $<

clean:
	rm -rf build