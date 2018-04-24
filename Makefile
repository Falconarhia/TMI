TMI: mkdir_bin tmi.o double_linked_list.o instruction_list.o parser.o mt.o tmi.o main.o
	gcc -std=c99 -Wall -Werror build/tmi.o build/double_linked_list.o build/instruction_list.o build/parser.o build/mt.o build/main.o -o bin/TMI


double_linked_list.o: mkdir_build src/double_linked_list.c
	gcc -std=c99 -Wall -Werror -c src/double_linked_list.c -o build/double_linked_list.o

instruction_list.o: mkdir_build src/instruction_list.c
	gcc -std=c99 -Wall -Werror -c src/instruction_list.c -o build/instruction_list.o

parser.o: mkdir_build src/parser.c
	gcc -std=c99 -Wall -Werror -c src/parser.c -o build/parser.o

mt.o: mkdir_build src/mt.c
	gcc -std=c99 -Wall -Werror -c src/mt.c -o build/mt.o

tmi.o: mkdir_build src/tmi.c
	gcc -std=c99 -Wall -Werror -c src/tmi.c -o build/tmi.o

main.o: mkdir_build src/main.c
	gcc -std=c99 -Wall -Werror -c src/main.c -o build/main.o

mkdir_bin:
	if [ ! -d "bin" ]; then mkdir bin; fi
	
mkdir_build:
	if [ ! -d "build" ]; then mkdir build; fi
	if [ ! -d "build/test" ]; then mkdir build/test; fi

.PHONY:clean test
clean: 
	rm -rf bin build