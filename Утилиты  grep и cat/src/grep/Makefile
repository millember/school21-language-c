CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = s21_grep
SOURCES = s21_grep.c

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

rebuild: clean all