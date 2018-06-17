all: build bin bin/TMI

CFLAGS  = -Wall -Werror -std=c99 -lncurses
bin/TMI: build/double_linked_list.o \
	build/instruction_list.o build/parser.o build/mt.o build/tmi.o build/main.o
	gcc $(CFLAGS) build/main.o build/tmi.o build/double_linked_list.o \
	build/instruction_list.o \
	build/parser.o build/mt.o -o bin/TMI -lcurses -lpthread

test: build bin bin/TMI_TEST
	bin/TMI_TEST

bin/TMI_TEST: build/test/dll_test.o build/test/test_instruction.o build/test/test_parser.o build/test/main.o \
	build/instruction_list.o build/double_linked_list.o build/parser.o \
	build/mt.o build/tmi.o build/test/test_mt.o build/tmi.o build/test/test_tmi.o
	gcc -std=c99 -Wall -Werror build/double_linked_list.o \
	build/instruction_list.o \
	build/parser.o \
	build/mt.o \
	build/tmi.o \
	build/test/dll_test.o \
	build/test/test_parser.o \
	build/test/test_instruction.o \
	build/test/test_mt.o \
	build/test/test_tmi.o \
	build/test/main.o -o bin/TMI_TEST

build/double_linked_list.o: src/double_linked_list.c
	gcc -std=c99 -Wall -Werror -c src/double_linked_list.c \
	-o build/double_linked_list.o

build/instruction_list.o: src/instruction_list.c
	gcc -std=c99 -Wall -Werror -c src/instruction_list.c \
	-o build/instruction_list.o

build/parser.o: src/parser.c
	gcc -std=c99 -Wall -Werror -c src/parser.c -o build/parser.o

build/mt.o: src/mt.c
	gcc -std=c99 -Wall -Werror -c src/mt.c -o build/mt.o

build/tmi.o: src/tmi.c
	gcc -std=c99 -Wall -Werror -c src/tmi.c -o build/tmi.o

build/main.o: src/main.c
	gcc $(CFLAGS) -c src/main.c -o build/main.o

build/test/dll_test.o: test/test_dll.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_dll.c -o build/test/dll_test.o

build/test/test_instruction.o: test/test_instruction.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_instruction.c -o build/test/test_instruction.o

build/test/test_parser.o: test/test_parser.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_parser.c -o build/test/test_parser.o

build/test/test_mt.o: test/test_mt.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_mt.c -o build/test/test_mt.o

build/test/test_tmi.o: test/test_tmi.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_tmi.c -o build/test/test_tmi.o

build/test/main.o: test/main.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/main.c -o build/test/main.o

bin:
	mkdir bin
	
build:
	mkdir build
	mkdir build/test

.PHONY:clean test all
clean: 
	rm -rf bin build