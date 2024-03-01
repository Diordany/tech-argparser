# Project directories:
dir_src := src
dir_inc := include
dir_obj := obj
dir_bin := bin

dirs_inc := $(dir_inc)

# Tools:
cc := g++
ld := $(cc)

# Precompiler flags:
iflags := $(patsubst %,-I%,$(dirs_inc))

# Compiler flags:
cflags := -std=gnu++17 -Wall -g3

# Object list:
obj_names :=\
		arg-parser\
		main

obj_files := $(patsubst %,$(dir_obj)/%.o,$(obj_names))

# Binary list:
bin := $(dir_bin)/argparser

all: $(bin)

rebuild: clean $(bin)

run: $(bin)
	$(bin)

clean:
	rm -rf $(dir_obj) $(dir_bin)

# Directories
$(dir_obj):
	mkdir -p $@

$(dir_bin):
	mkdir -p $@

# Objects:
$(dir_obj)/%.o: $(dir_src)/%.cpp | $(dir_obj)
	$(cc) -c $(strip $(cflags) $(iflags)) -o $@ $<

# Binaries:
$(bin): $(obj_files) | $(dir_bin)
	$(ld) -o $@ $^