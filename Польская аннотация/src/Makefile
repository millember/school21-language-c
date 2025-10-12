.SILENT:
all:
	gcc -Wall -Wextra -Werror -std=c11 polish_note.c main.c input.c graph.c -o ../build/Quest_1 -lm
clean:
	rm -rf ../build/Quest_1
rebuild: clean all

start:
	../build/Quest_1
clang:
	cp ../materials/linters/.clang-format ../src
	clang-format -n *.c
	clang-format -n *.h
	clang-format -i *.c
	clang-format -i *.h
	rm -rf .clang-format
add:
	git add ../build/*
	git add .

