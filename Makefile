CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Werror -Wextra
SANFLAG=#-fsanitize=address -g
COVFLAGS=-fprofile-arcs -ftest-coverage

# Директории и исходники
BUILD_DIR = ./build
TARGET = tetris
MAIN_O = tetris_main.o
OUT_TARGET = $(BUILD_DIR)/Play_$(TARGET)
LIBRARY = brick_game/$(TARGET)/$(TARGET)_backend.a

FRONT_DIR = gui/cli
FRONT_FILES = $(wildcard $(FRONT_DIR)/*.c)
FRONT_O_FILES = $(subst .c,.o, $(FRONT_FILES))

BACK_DIR = brick_game/$(TARGET)
BACK_FILES = $(wildcard $(BACK_DIR)/*.c)
BACK_O_FILES = $(subst .c,.o, $(BACK_FILES))
O_GCOV_FILES = $(addsuffix .gcov, $(BACK_O_FILES))

TEST_DIR=./tests
C_TEST_FILES=$(wildcard $(TEST_DIR)/*.c)
O_TEST_FILES = $(subst .c,.o, $(C_TEST_FILES))
OUT_TEST=$(TEST_DIR)/test.out

DIST_DIR = dist
ARCHIVE_NAME = brick_game_v1.tar.gz
SRC_FILES = *

# Флаги для библиотеки check
OS=$(shell uname)
PROC=$(shell uname -m)
CHECKFLAGS=-lcheck -lm
ifeq ($(OS)_$(PROC),Darwin_arm64)
# Для M процессоров мака доп флаг (расскоментить нижнюю строку)
	CFLAGS += -Wno-gnu-zero-variadic-macro-arguments
else ifneq ($(OS), Darwin)
# Для Линукс доп флаги свои
	CHECKFLAGS += -lsubunit -lrt -lpthread
	CFLAGS += -D_POSIX_C_SOURCE=199309L
endif

all: $(LIBRARY)

# Собираем библиотеку
$(LIBRARY): $(BACK_O_FILES)
	ar rcs $@ $^
	ranlib $@

# Компилируем объектные файлы функций библиотеки с профилир/покрытием
%.o.gcov: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $(COVFLAGS) $< -o $(subst $(BACK_DIR), $(TEST_DIR), $@)

# Компилируем объектные файлы библиотеки и тестов
%.o: %.c
	$(CC) $(CFLAGS) -c $(SANFLAG) $< -o $@

test: uninstall $(O_GCOV_FILES) $(O_TEST_FILES)
	$(CC) $(CFLAGS) $(SANFLAG) $(COVFLAGS) $(O_TEST_FILES) $(subst $(BACK_DIR), $(TEST_DIR), $(O_GCOV_FILES)) \
	-o $(OUT_TEST) $(CHECKFLAGS)

	$(OUT_TEST)

gcov_report:
	(cd $(TEST_DIR) && gcov *.o.gcov)
	@echo ""
	lcov -t "test" -o $(TEST_DIR)/report.info -c -d $(TEST_DIR)
	genhtml -o $(TEST_DIR)/report $(TEST_DIR)/report.info
	open $(TEST_DIR)/report/index.html

clang:
	clang-format -n $(BACK_DIR)/*.c $(FRONT_DIR)/*.c $(TEST_DIR)/*.c inc/*.h
	clang-format -i $(BACK_DIR)/*.c $(FRONT_DIR)/*.c $(TEST_DIR)/*.c inc/*.h

clean:
	find . -type f -name "*.o" -delete
	find . -type f -name "*.gc*" -delete
# {} - find заменяет его на текущий найденный элемент
#  + - find передаст все найденное в команду rm -rf одним вызовом, как rm -rf file1 dir2
	rm -rf $(TEST_DIR)/report $(DIST_DIR)
	rm -f $(LIBRARY) $(OUT_TEST)
	rm -rf doxygen

rebuild: clean all

# Дистрибутив (архив проекта)
dist: clean
	mkdir -p $(DIST_DIR)
	@tar -czvf $(DIST_DIR)/$(ARCHIVE_NAME) $(SRC_FILES)
	@echo "Distribution package created: $(DIST_DIR)/$(ARCHIVE_NAME)"

# Документация
dvi:
	rm -rf doxygen
	doxygen && open doxygen/html/index.html

# Установка и запуск
install: installdirs $(LIBRARY) $(FRONT_O_FILES) $(MAIN_O)
	$(CC) $(CFLAGS) $(SANFLAG) $(FRONT_O_FILES) $(MAIN_O) $(LIBRARY) -o $(OUT_TARGET) -lncurses

installdirs:
	mkdir -p $(BUILD_DIR)

reinstall_and_start: clean uninstall install start

uninstall:
		rm -rf $(BUILD_DIR)

start: 
	$(OUT_TARGET)

# Докер и валгринд
NAME = chickpet$(TARGET)
docker:
	docker build -t $(NAME):v1 .
	docker run -it --name $(NAME) $(NAME):v1 /bin/bash

renew_docker: clean
	docker start $(NAME)
	docker exec $(NAME) rm -rf /code
	docker cp . $(NAME):/code
	docker exec -it $(NAME) /bin/bash

delete_docker:
	docker stop $(NAME)
	docker rm $(NAME)
	docker rmi $(NAME):v1

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--log-file=leaks_log.txt $(OUT_TEST); vim leaks_log.txt