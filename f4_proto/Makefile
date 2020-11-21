PROJECT = f4_proto
BUILD_DIR = bin

CFILES = leds.pb.c main.c

# Nanopb
SHARED_DIR = ../nanopb ../proto
CFILES += pb_encode.c pb_decode.c pb_common.c

CFLAGS = -Wextra -Werror

DEVICE=stm32f411vet6
OOCD_FILE = board/stm32f4discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk

../proto/leds.pb.c:
	$(MAKE) -C ../proto
