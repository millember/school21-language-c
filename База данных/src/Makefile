CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = modules_db
SOURCES = modules_db.c shared.c master_modules.c master_levels.c master_status_events.c index.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

build_db: $(TARGET)

clean:
	rm -f $(TARGET)
	rm -f ../materials/*.index

.PHONY: build_db clean