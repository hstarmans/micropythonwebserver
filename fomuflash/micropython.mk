EXAMPLE_MOD_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(EXAMPLE_MOD_DIR)/pythonwrap.c
# SRC_USERMOD += $(EXAMPLE_MOD_DIR)/fomu-flash.c
# SRC_USERMOD += $(EXAMPLE_MOD_DIR)/fpga.c
# SRC_USERMOD += $(EXAMPLE_MOD_DIR)/ice40.c
# SRC_USERMOD += $(EXAMPLE_MOD_DIR)/rpi.c
# SRC_USERMOD += $(EXAMPLE_MOD_DIR)/spi.c

# We can add our module folder to include paths if needed
# This is not actually needed in this example.
CFLAGS_USERMOD += -I$(EXAMPLE_MOD_DIR) 
CEXAMPLE_MOD_DIR := $(USERMOD_DIR)
