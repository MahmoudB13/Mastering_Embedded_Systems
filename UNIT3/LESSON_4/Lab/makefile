CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -gdwarf-2 -g
INCS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
AS_OBJ = $(AS:.s=.o)
PROJECT_NAME = Cortex_M4

all:$(PROJECT_NAME).bin
	@echo BUILD COMPLETE...

%.o: %.c
	$(CC)gcc.exe -c  $(CFLAGS) $(INCS) $< -o $@

$(PROJECT_NAME).elf: $(OBJ) $(AS_OBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AS_OBJ) -o $@ -Map=output.map
	cp $(PROJECT_NAME).elf $(PROJECT_NAME).axf
$(PROJECT_NAME).bin: $(PROJECT_NAME).elf
	$(CC)objcopy.exe -O binary $< $@

clear:
	rm *.elf *.bin

clear_all:
	rm *.elf *.bin *.map *.o