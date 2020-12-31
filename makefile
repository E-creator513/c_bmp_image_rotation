CC = gcc
APP = rotator 
CFLAGS = -std=c18 -pedantic -Wall -Werror
SRC_DIR = src/
BUILD_DIR = build/

c_src_files := $(wildcard $(SRC_DIR)*.c)
obj_files := $(addsuffix .o, $(basename $(notdir $(c_src_files))))


define build-obj
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)$@
endef

$(APP): $(obj_files)
	$(CC) -o $(BUILD_DIR)$(APP) $(^:%=$(BUILD_DIR)%)

clean:
	rm -rf $(BUILD_DIR)*

%.o: $(SRC_DIR)%.c
	$(call build-obj)