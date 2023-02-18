CFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a

build: s21_matrix_oop.C
	gcc -c $(CFLAGS) -lstdc++ -std=c++17 s21_matrix_oop.C -o s21_matrix_oop.o

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

clean:
	rm -rf *.o *.out s21_matrix_oop.a unit_test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report

rebuild:
	make clean
	make build

leaks: 
	leaks -atExit -- ./a.out

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cpp *.h
	rm .clang-format

test: s21_matrix_oop.a ./unit_tests/unit_tests.C
	gcc -lgtest -lstdc++ -std=c++17 s21_matrix_oop.a ./unit_tests/unit_tests.C -o unit_test
	./unit_test

gcov_report:
	gcc  --coverage ./unit_tests/unit_tests.C s21_matrix_oop.C -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html