# Project Name
TARGET = cav-x

# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# CPU Flags
CPU = -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16

# Directories & Files
LDSCRIPT = core/stm32h753xx.ld
SRCS = core/reset.c

# Compiler Flags
CFLAGS = $(CPU) -O0 -g3 -Wall -Icore --specs=nosys.specs

# Linker Flags
LDFLAGS = $(CPU) -T$(LDSCRIPT) -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections

# Build Rules
all: $(TARGET).bin

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f *.elf *.bin *.map