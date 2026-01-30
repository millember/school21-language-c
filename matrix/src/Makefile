CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage
SRC = s21_matrix.c
TEST_SRC = s21_test.c
OBJS = $(SRC:.c=.o)
OS := $(shell uname -s)
LEAKS = CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --read-var-info=yes ./unit_test

ifeq ($(OS),Linux)
  LIBS = -lcheck -lm -lrt -lpthread -lsubunit
  OPEN_CMD = xdg-open
else ifeq ($(OS),Darwin)
  LIBS = -lcheck -lm -lpthread
  OPEN_CMD = open
endif

.PHONY: test rt all clean c_format leaks valgrind_all clean_without_report gcov_report

all: s21_matrix.a

s21_matrix.a: $(OBJS)
	ar rcs s21_matrix.a $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

rt: clean test leaks

test: clean c_format s21_matrix.a s21_test.o 
	clear
	$(CC) $(CFLAGS) s21_test.o s21_matrix.a -o unit_test $(LIBS)
	./unit_test

s21_test.o: 
	$(CC) $(CFLAGS) -c s21_test.c -o s21_test.o

gcov_report: clean
	# Компилируем с флагами gcov
	$(CC) $(GCOVFLAGS) $(TEST_SRC) $(SRC) -o gcov_unit_test $(LIBS)
	
	# Запускаем тесты
	./gcov_unit_test
	
	# Создаем директорию для отчета
	@mkdir -p report
	
	# Генерируем HTML отчет, исключая тестовые файлы
	gcovr --html --html-details -o report/coverage.html \
	      --exclude=".*test.*" \
	      --exclude="test"
	gcovr --print-summary --exclude=".*test.*" --exclude="test"
	
	# Открываем отчет
	$(OPEN_CMD) ./report/coverage.html
	@echo "HTML coverage report generated: report/coverage.html"

# Альтернативная версия с более точной фильтрацией
gcov_report_filtered: clean
	# Компилируем с флагами gcov
	$(CC) $(GCOVFLAGS) $(TEST_SRC) $(SRC) -o gcov_unit_test $(LIBS)
	
	# Запускаем тесты
	./gcov_unit_test
	
	# Создаем директорию для отчета
	@mkdir -p report
	
	@echo "Generating coverage report..."
	@echo "=== Coverage summary (excluding test files) ==="
	gcovr -r . \
	      --filter="s21_matrix.c" \
	      --exclude="s21_test.c" \
	      --exclude=".*test.*" \
	      --print-summary
	
	@echo "=== Generating HTML report ==="
	gcovr -r . \
	      --filter="s21_matrix.c" \
	      --exclude="s21_test.c" \
	      --exclude=".*test.*" \
	      --html --html-details -o report/coverage.html
	
	@echo "=== Branch coverage ==="
	gcovr -r . \
	      --filter="s21_matrix.c" \
	      --exclude="s21_test.c" \
	      --exclude=".*test.*" \
	      --branches
	
	# Открываем отчет
	$(OPEN_CMD) ./report/coverage.html

c_format:
	clang-format -style=Google -i *.c *.h

valgrind_all: clean c_format s21_matrix.a s21_test.o
	$(CC) $(CFLAGS) s21_test.o s21_matrix.a -o unit_test $(LIBS)
	@echo "================================================"
	@echo "Running valgrind for ALL tests..."
	@echo "================================================"
	$(LEAKS) ./unit_test 2>&1 | tee valgrind_log.txt
	@echo ""
	@echo "Valgrind log saved to valgrind_log.txt"

leaks: 
	$(LEAKS)

clean_without_report: 
	rm -f *.o *.gcno *.gcov *.gcda gcov_unit_test output.txt *.info *.a main_test unit_test s21_matrix s21_matrix_gcov.o s21_test_gcov.o s21_matrix_gcov.a test

clean: clean_without_report
	rm -rf report gcov_unit_test