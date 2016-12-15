BASE_PATH=$(PWD)
export BASE_PATH

PORT=/dev/ttyACM0
BOARD_TYPE=arduino
BAUD_RATE=115200
AVRDUDE=/usr/bin/avrdude
AVRDUDE_CONF=/etc/avrdude.conf

ARTIFACTS_DIR=$(PWD)/artifacts

all:		images

clean:
		@echo '# *** Cleaning...'
		rm -rf $(ARTIFACTS_DIR)
		make -C apps clean

images: $(ARTIFACTS_DIR) apps
	make -C apps install INSTALL_DIR=$(ARTIFACTS_DIR)

$(ARTIFACTS_DIR):
	mkdir -p $(ARTIFACTS_DIR)

reset:
		@echo '# *** Resetting...'
		stty --file $(PORT) hupcl
		sleep 0.1
		stty --file $(PORT) -hupcl

vpath %.hex $(ARTIFACTS_DIR)/

upload-IMUSensorTest : IMUSensorTest.hex

include $(BASE_PATH)/cpu.mk

upload-% : %.hex
		@echo '# *** Uploading...'
		$(AVRDUDE) -q -V -p $(MCU) -C $(AVRDUDE_CONF) -c $(BOARD_TYPE) \
		           -b $(BAUD_RATE) -P $(PORT) \
			   -U flash:w:$^:i
		@echo '# *** Done - enjoy your sketch!'

terminal:
	picocom $(PORT) -b $(BAUD_RATE)
