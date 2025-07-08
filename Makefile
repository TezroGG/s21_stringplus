# Компилятор и утилиты
CC = gcc
AR = ar

# Флаги компиляции и линковки
CFLAGS = -Wall -Werror -Wextra -std=c11
COVERAGE_FLAGS = --coverage
LDFLAGS = -lcheck -lsubunit -lpthread -lm -lrt
ARFLAGS = cr

TEST_DIR = test

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
# Отдельные объектные файлы для gcov
GCOV_OBJ_FILES = $(SRC_FILES:%.c=%.gcov.o)

TEST_SRC = $(TEST_DIR)/s21_string_test.c
TEST_OBJ = $(TEST_SRC:.c=.o)

LIB = s21_string.a
GCOV_LIB = s21_string_gcov.a
EXE = $(TEST_DIR)/s21_string_test

# Основные цели
.PHONY: all test gcov_report clean rebuild clang clangch leaks valgrind

# Сборка библиотеки
all: $(LIB)

$(LIB): $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $(OBJ_FILES)

# Сборка библиотеки с поддержкой gcov
$(GCOV_LIB): $(GCOV_OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $(GCOV_OBJ_FILES)

# Правило компиляции для обычных объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Правило компиляции для объектных файлов с поддержкой gcov
%.gcov.o: %.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# Правило для создания объектных файлов из тестов
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(COVERAGE_FLAGS) -c $< -o $@

# Сборка и запуск тестов с библиотекой с поддержкой gcov
test: $(GCOV_LIB) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(GCOV_LIB) $(LDFLAGS) $(COVERAGE_FLAGS) -lgcov -o $(EXE)
	./$(EXE)

# Генерация отчёта покрытия
gcov_report: test
	lcov -t "Report" -c -d . -d $(TEST_DIR) --output-file coverage.info
	genhtml coverage.info --output-directory out
	xdg-open out/index.html || firefox out/index.html || google-chrome out/index.html

# Очистка сгенерированных файлов
clean:
	rm -f *.o *.gcov.o $(TEST_DIR)/*.o *.gcno $(TEST_DIR)/*.gcno *.gcda $(TEST_DIR)/*.gcda $(LIB) $(GCOV_LIB) $(EXE) coverage.info
	rm -rf out

# Полная сборка и очистка
rebuild: clean all

# Форматирование кода
clang:
	clang-format -i -style=Google *.c $(wildcard $(TEST_DIR)/*.c)

# Проверка форматирования
clangch:
	clang-format -n -style=Google *.c $(wildcard $(TEST_DIR)/*.c)

# Проверка на утечки с использованием Valgrind
leaks: test
	valgrind --track-origins=yes --leak-check=full ./$(EXE) > /dev/null

# Основная проверка с использованием Valgrind
valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./$(EXE) > /dev/null
