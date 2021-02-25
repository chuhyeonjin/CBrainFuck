CC := gcc-10
CFLAGS := -Wall
BUILD := ../build
TARGET := $(BUILD)/BrainFuck

all: $(BUILD)/main.o $(BUILD)/print.o
	@$(CC) $(CFLAGS) -o $(TARGET) $^

$(BUILD)/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^