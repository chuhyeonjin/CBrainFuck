CC := gcc-10
CFLAGS := -Wall -std=c11
BUILD := ../build
TARGET := $(BUILD)/BrainFuck

all: $(BUILD)/main.o
	@$(CC) $(CFLAGS) -o $(TARGET) $^

$(BUILD)/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^