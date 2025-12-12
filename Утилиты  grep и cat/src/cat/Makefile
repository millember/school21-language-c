CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = s21_cat
SOURCES = s21_cat.c
HEADERS = s21_cat.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild