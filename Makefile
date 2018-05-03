TMI: mkdir_bin tmi.o double_linked_list.o \
	instruction_list.o parser.o mt.o tmi.o main.o
	gcc -std=c99 -Wall -Werror -lncurses -lpthread \
	build/tmi.o build/double_linked_list.o \
	build/instruction_list.o build/parser.o build/mt.o build/main.o -o bin/TMI

test: TMI_TEST
	bin/TMI_TEST

TMI_TEST: dll_test.o test_instruction.o test_parser.o main_test.o \
	instruction_list.o double_linked_list.o parser.o \
	mt.o tmi.o test_mt.o tmi.o test_tmi.o
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

double_linked_list.o: mkdir_build src/double_linked_list.c
	gcc -std=c99 -Wall -Werror -c src/double_linked_list.c \
	-o build/double_linked_list.o

instruction_list.o: mkdir_build src/instruction_list.c
	gcc -std=c99 -Wall -Werror -c src/instruction_list.c \
	-o build/instruction_list.o

parser.o: mkdir_build src/parser.c
	gcc -std=c99 -Wall -Werror -c src/parser.c -o build/parser.o

mt.o: mkdir_build src/mt.c
	gcc -std=c99 -Wall -Werror -c src/mt.c -o build/mt.o

tmi.o: mkdir_build src/tmi.c
	gcc -std=c99 -Wall -Werror -c src/tmi.c -o build/tmi.o

main.o: mkdir_build src/main.c
	gcc -std=c99 -Wall -Werror -c src/main.c -o build/main.o

dll_test.o: double_linked_list.o test/test_dll.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_dll.c -o build/test/dll_test.o

test_instruction.o: test/test_instruction.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_instruction.c -o build/test/test_instruction.o

test_parser.o: test/test_parser.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_parser.c -o build/test/test_parser.o

test_mt.o: test/test_mt.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_mt.c -o build/test/test_mt.o

test_tmi.o: test/test_tmi.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/test_tmi.c -o build/test/test_tmi.o

main_test.o: test/main.c
	gcc -std=c99 -Wall -Werror -I thirdparty -I src \
	-c test/main.c -o build/test/main.o

mkdir_bin:
	if [ ! -d "bin" ]; then mkdir bin; fi
	
mkdir_build:
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/test" ]; then mkdir build/test; fi

.PHONY:clean test
clean: 
	rm -rf bin build