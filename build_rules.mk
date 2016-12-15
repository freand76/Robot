# Hey Emacs, this is a -*- makefile -*-

include $(BASE_PATH)/cpu.mk

CC=/usr/bin/avr-gcc
CPP=/usr/bin/avr-g++
OBJCOPY=/usr/bin/avr-objcopy 

ARDUINO_DIR=/usr/share/arduino
ARDUINO_CORE=$(ARDUINO_DIR)/hardware/arduino/cores/arduino
ARDUINO_VARIANT=$(ARDUINO_DIR)/hardware/arduino/variants/standard
ARDUINO_LIBRARY=$(ARDUINO_DIR)/libraries/
AVR_INCLUDE=/usr/lib/avr/include

INCLUDE= \
	-I. \
	-I$(BASE_PATH)/src \
	-I$(ARDUINO_CORE) \
	-I$(ARDUINO_VARIANT) \
	-I$(AVR_INCLUDE) \
	-I$(ARDUINO_LIBRARY)/Wire \
	-I$(ARDUINO_LIBRARY)/Wire/utility

CC_FLAGS=-g -Os -w -Wall -ffunction-sections -fdata-sections -fno-exceptions -std=gnu99
CPP_FLAGS=-g -Os -w -Wall -ffunction-sections -fdata-sections -fno-exceptions

vpath %.cpp .
vpath %.cpp $(BASE_PATH)/src/
vpath %.c  $(ARDUINO_CORE)/
vpath %.cpp $(ARDUINO_CORE)/
vpath %.cpp $(ARDUINO_LIBRARY)/Wire
vpath %.c  $(ARDUINO_LIBRARY)/Wire/utility

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(PROGRAM).elf : $(OBJ_FILES)
	$(CC) -mmcu=$(MCU) -lm -Wl,--gc-sections -Os -o $@ $^

$(PROGRAM).hex : $(PROGRAM).elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

$(BUILD_DIR)/%.o : %.cpp
	$(CPP) -c -mmcu=$(MCU) -DF_CPU=$(DF_CPU) $(INCLUDE) \
	$(CPP_FLAGS) $^ -o $@

$(BUILD_DIR)/%.o : %.c
	$(CC) -c -mmcu=$(MCU) -DF_CPU=$(DF_CPU) $(INCLUDE) \
	$(CC_FLAGS) $^ -o $@

