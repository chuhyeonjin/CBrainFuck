DEBUG := true

CC := gcc-10
CFLAGS := -Wall -std=c11
BUILD := ../build
TARGET := $(BUILD)/BrainFuck
DEBUG_TARGET := $(BUILD)/debug

ifeq ($(DEBUG), true)
CFLAGS := $(CFLAGS) -g
TARGET := $(DEBUG_TARGET)
endif

$(TARGET): $(BUILD)/main.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^