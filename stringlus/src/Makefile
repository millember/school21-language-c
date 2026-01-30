CC = gcc
CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
CFLAGS = -Wall -Wextra -Werror -std=c11 -Wno-format $(CHECK_CFLAGS)

GCOV_FLAGS = -fprofile-arcs -ftest-coverage
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIB_SRC = $(wildcard s21_*.c) \
          $(wildcard sprintf/*.c) \
          $(wildcard sscanf/*.c)

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    # macOS: нет libgcov
    GCOV_LIBS =
else
    # Linux: libgcov требуется
    GCOV_LIBS = -lgcov
endif

# Все .c в корне и подпапках
SRC := $(wildcard *.c */*.c)

# Удаляем тесты
SRC := $(filter-out tests/%, $(SRC))


TEST := $(wildcard tests/*.c)

TEST_BIN = test_runner

LIBS = `pkg-config --libs check` -lm -lpthread
# Object files
LIB_OBJ = $(LIB_SRC:.c=.o)

FMT_ROOT_C := $(wildcard *.c)
FMT_ROOT_H := $(wildcard *.h)
FMT_SUB_C  := $(wildcard */*.c)
FMT_SUB_H  := $(wildcard */*.h)

FMT_FILES := $(FMT_ROOT_C) $(FMT_ROOT_H) $(FMT_SUB_C) $(FMT_SUB_H)


.PHONY: all s21_string.a clean test sanitizer gcov_report clang cppcheck rebuild

all: s21_string.a

# Требование Школы 21: библиотека
s21_string.a: $(LIB_OBJ)
	ar rcs s21_string.a $(LIB_OBJ)
	ranlib s21_string.a

%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


test: s21_string.a
	$(CC) $(CFLAGS) $(SRC) $(TEST) -o $(TEST_BIN) $(LIBS)
	./$(TEST_BIN)

# -----------------------
#     GCOV ОТЧЁТ
# -----------------------


gcov_report: clean
	mkdir -p logs
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC) $(TEST) -o logs/$(TEST_BIN) $(LIBS) $(GCOV_LIBS)
	./logs/$(TEST_BIN)
	gcovr --html-details logs/report.html \
	      --exclude 'tests/*' \
	      --print-summary
	@echo "HTML-отчёт: logs/report.html"
	@open logs/report.html 2>/dev/null || true

# -----------------------
#     CLANG FORMAT
# -----------------------
clang:
	@if [ -n "$(FMT_FILES)" ]; then \
	    clang-format -n $(FMT_FILES); \
	    clang-format -i $(FMT_FILES); \
	else \
	    echo "Нет файлов для форматирования."; \
	fi

	

# -----------------------
#       CPPCHECK
# -----------------------
cppcheck:
	cppcheck --enable=all \
	         --suppress=missingIncludeSystem \
	         --suppress=unusedStructMember \
	         --suppress=unmatchedSuppression \
	         --suppress=checkersReport \
	         *.c */*.c *.h */*.h

clean:
	rm -f $(TEST_BIN)
	rm -f s21_string.a
	rm -rf logs
	find . -name '*.gcda' -delete
	find . -name '*.gcno' -delete
	rm -f *.o
	rm -f */*.o

rebuild: clean all