# Переменные
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -O2 -fprofile-arcs -ftest-coverage -I. --coverage
LDFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage
OBJ_DIR = objects
COV_DIR = coverage
SRC_FILES = s21_matrix_oop.cc unit_tests.cc
OBJ_FILES = $(patsubst %.cc,$(OBJ_DIR)/%.o,$(SRC_FILES))
TARGET = s21_matrix_oop.a
TEST_TARGET = test
TEST_FLAGS = -lgtest -pthread

# Основное правило
all: $(TARGET) test coverage format-check valgrind open_coverage

# Создание и запуска тестов
test: $(TARGET)
	g++ $(CXXFLAGS) unit_tests.cc $(TEST_FLAGS) $(TARGET) -o $(OBJ_DIR)/$(TEST_TARGET)
	./$(OBJ_DIR)/$(TEST_TARGET)

# Создание каталога для объектных файлов
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Правила для сборки объектных файлов
$(OBJ_DIR)/%.o: %.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для сборки статической библиотеки
$(TARGET): $(OBJ_FILES)
	ar rcs $(TARGET) $(OBJ_FILES)

# Правило для сборки исполняемого файла тестов
$(OBJ_DIR)/$(TEST_TARGET): $(TARGET)
	g++ $(OBJ_FILES) $(LDFLAGS) -o $(OBJ_DIR)/$(TEST_TARGET)

# Очистка промежуточных файлов
clean:
	rm -rf $(OBJ_DIR) $(COV_DIR) *.gcda *.gcno *.gcov coverage.info valgrind.log $(TARGET)

# Правило для покрытия тестами
coverage: $(TARGET)
	./$(OBJ_DIR)/$(TEST_TARGET)
	mkdir -p $(COV_DIR)
	lcov --capture --directory . --output-file coverage.info --no-external
	genhtml coverage.info --output-directory $(COV_DIR) --no-function-coverage

# Открытие отчета о покрытии
open_coverage:
	@xdg-open $(COV_DIR)/index.html || echo "Невозможно открыть отчет о покрытии."

# Форматирование кода
format-check:
	clang-format -n s21_matrix_oop.cc unit_tests.cc s21_matrix_oop.h

# Проверка на утечки памяти
valgrind: test
	 valgrind --tool=memcheck --leak-check=yes --log-file="valgrind.log" ./$(OBJ_DIR)/$(TEST_TARGET)

.PHONY: all clean test coverage open_coverage format-check valgrind
