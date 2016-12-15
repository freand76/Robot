PROGRAM=MotorTest
BUILD_DIR=.obj
include ../arduino-src.mk

## FILES in /src
CPP_FILES += \
	MotorTest.cpp \
	MotorControl.cpp

OBJ_FILES =
OBJ_FILES += $(addprefix $(BUILD_DIR)/,$(C_FILES:.c=.o))
OBJ_FILES += $(addprefix $(BUILD_DIR)/,$(CPP_FILES:.cpp=.o))
PROGRAM := $(addprefix $(BUILD_DIR)/,$(PROGRAM))

all:	$(BUILD_DIR) $(PROGRAM).hex

include ../../build_rules.mk

clean:
		@echo '# *** Cleaning...'
		rm -rf $(BUILD_DIR)

install: all
	@mkdir -p $(INSTALL_DIR)
	cp $(PROGRAM).hex $(INSTALL_DIR)
