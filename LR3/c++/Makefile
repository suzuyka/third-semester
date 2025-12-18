CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -DGTEST_HAS_PTHREAD=1
TEST_LIBS = -lgtest -lpthread
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage

BENCHMARK_DIR = benchmarks
BENCHMARK_SRCS = $(wildcard $(BENCHMARK_DIR)/*.cpp)
BENCHMARK_OBJS = $(patsubst $(BENCHMARK_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(BENCHMARK_SRCS))
BENCHMARK_TARGET = $(BIN_DIR)/educational_benchmark
BENCHMARK_LIBS = -lbenchmark -lpthread

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
COVERAGE_DIR = coverage
DOCS_DIR = docs

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
MAIN_OBJ = $(OBJ_DIR)/main.o

TARGET = $(BIN_DIR)/main

# Тестовые объекты
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))
TEST_TARGETS = $(patsubst $(TEST_DIR)/%.cpp, $(BIN_DIR)/%, $(TEST_SRCS))

# =============================================================================
# ОСНОВНЫЕ КОМАНДЫ
# =============================================================================

.PHONY: all build run clean help

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MAIN_OBJ): main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(COVERAGE_DIR) $(DOCS_DIR)/html $(DOCS_DIR)/latex

help:
	@echo "Доступные команды:"
	@echo "  make              # Сборка проекта"
	@echo "  make run          # Запуск"
	@echo "  make test         # Тесты"
	@echo "  make coverage     # Покрытие кода"
	@echo "  make benchmark    # Сборка benchmark"
	@echo "  make benchmark-run # Сборка и запуск benchmark"
	@echo "  make lint         # Линтинг"
	@echo "  make documentation # Документация + UML"
	@echo "  make clean        # Очистка"

# =============================================================================
# ТЕСТИРОВАНИЕ
# =============================================================================

.PHONY: test

test: $(TEST_TARGETS)
	@for test in $(TEST_TARGETS); do \
		echo "Running $$test..."; \
		$$test; \
	done

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(OBJS) $(OBJ_DIR)/test_main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LIBS)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/test_main.o: $(TEST_DIR)/test_main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================================================================
# ПОКРЫТИЕ КОДА
# =============================================================================

.PHONY: coverage

coverage:
	@echo "Building with coverage flags..."
	$(MAKE) clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) $(COVERAGE_FLAGS)" test
	@mkdir -p $(COVERAGE_DIR)
	@echo "Generating coverage report..."
	lcov --capture --directory $(OBJ_DIR) --output-file $(COVERAGE_DIR)/coverage.info --ignore-errors mismatch
	lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' '$(TEST_DIR)/*' --output-file $(COVERAGE_DIR)/coverage.info
	genhtml $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)/report
	@echo "Coverage report: $(COVERAGE_DIR)/report/index.html"

# =============================================================================
# BENCHMARK
# =============================================================================

.PHONY: benchmark benchmark-run

benchmark: $(BENCHMARK_TARGET)

benchmark-run: benchmark
	@echo "Запуск benchmark тестов..."
	./$(BENCHMARK_TARGET)

$(BENCHMARK_TARGET): $(BENCHMARK_OBJS) $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BENCHMARK_LIBS)

$(OBJ_DIR)/%.o: $(BENCHMARK_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =============================================================================
# ЛИНТЕРЫ
# =============================================================================

.PHONY: lint lint-cppcheck lint-tidy

# CPPCheck
CPPCHECK = cppcheck
CPPCHECK_FLAGS = --enable=all --suppress=missingInclude --suppress=unusedFunction --inconclusive -I include

# Clang-tidy
CLANG_TIDY = clang-tidy
CLANG_TIDY_FLAGS = -checks='-*,readability-*,-readability-magic-numbers,-readability-identifier-length,clang-analyzer-*,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling' -header-filter='.*' -extra-arg=-std=c++17

# Файлы для линтинга
LINT_SRCS = $(SRCS) main.cpp
LINT_HEADERS = $(wildcard include/*.h)

lint: lint-cppcheck lint-tidy

lint-cppcheck:
	@echo "=== Running CPPCheck ==="
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(LINT_SRCS) $(LINT_HEADERS)

lint-tidy:
	@if command -v $(CLANG_TIDY) >/dev/null 2>&1; then \
		echo "=== Running Clang-Tidy ==="; \
		$(CLANG_TIDY) $(LINT_SRCS) $(CLANG_TIDY_FLAGS) -- -I include; \
	else \
		echo "=== Clang-Tidy not installed, skipping ==="; \
	fi

# =============================================================================
# ДОКУМЕНТАЦИЯ
# =============================================================================

.PHONY: documentation docs

documentation: docs

docs:
	@echo "Generating documentation..."
	@mkdir -p $(DOCS_DIR)
	@if command -v doxygen >/dev/null 2>&1; then \
		doxygen Doxyfile; \
		echo "Documentation generated: $(DOCS_DIR)/html/index.html"; \
	else \
		echo "Doxygen not installed. Install with: sudo apt-get install doxygen graphviz"; \
	fi

# =============================================================================
# ФИНАЛЬНЫЕ ЦЕЛИ
# =============================================================================

.PHONY: all test coverage clean run benchmark lint documentation docs help
