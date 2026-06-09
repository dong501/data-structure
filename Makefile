CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
TARGET  = emergency_queue
SRCDIR  = src
SRCS    = $(SRCDIR)/main.c \
          $(SRCDIR)/patient.c \
          $(SRCDIR)/circular_queue.c \
          $(SRCDIR)/priority_queue.c \
          $(SRCDIR)/stack.c \
          $(SRCDIR)/ui.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
