CLEAR		:= clear
CLANG		:= clang
CLANG_FLAGS	:= -Wall -Wextra -pedantic -std=c17 -g -lm
PROGRAM_FILE	:= main
VALGRIND	:= valgrind
VALGRIND_FLAGS	:= --leak-check=full --show-leak-kinds=all -s

.DEFAULT_GOAL := default
.PHONY: clean all run val bin test

default: help

help:	# help
	@printf '  Help yourself lol\n'
	@printf '         / \ \n'
	@printf '        |\_/|\n'
	@printf '        |---|\n'
	@printf '        |   |\n'
	@printf '        |   |\n'
	@printf '      _ |=-=| _\n'
	@printf '  _  / \|   |/ \ \n'
	@printf ' / \|   |   |   ||\ \n'
	@printf '|   |   |   |   | \> \n'
	@printf '|   |   |   |   |   \ \n'
	@printf '| -   -   -   - |)   )\n'
	@printf '|                   /\n'
	@printf ' \                 /\n'
	@printf '  \               /\n'
	@printf '   \             /\n'
	@printf '    \           /\n'

clean:	# cleans up project folder
	@printf '[\e[0;36mINFO\e[0m] Cleaning up folder...\n'
	rm -f $(PROGRAM_FILE)
	rm -f testreport.html

all:	# executes whole project with all flags and stuff lol
	@printf '[\e[0;36mINFO\e[0m] Executing with all flags...\n'
	$(CLEAR) && $(CLANG) $(CLANG_FLAGS) -o $(PROGRAM_FILE) *.c && $(VALGRIND) $(VALGRIND_FLAGS) ./$(PROGRAM_FILE)

run:	# executes whole project
	@printf '[\e[0;36mINFO\e[0m] Compiling and executing...\n'
	$(CLEAR) && $(CLANG) $(CLANG_FLAGS) -o $(PROGRAM_FILE) *.c && ./$(PROGRAM_FILE)

val:	# executes whole project with valgrind
	@printf '[\e[0;36mINFO\e[0m] Executing with all flags...\n'
	$(CLANG) $(CLANG_FLAGS) -o $(PROGRAM_FILE) *.c && $(VALGRIND) $(VALGRIND_FLAGS) ./$(PROGRAM_FILE)

bin:	# compiles the program
	@printf '[\e[0;36mINFO\e[0m] Executing with all flags...\n'
	$(CLANG) $(CLANG_FLAGS) -o $(PROGRAM_FILE) *.c

test:	# executes tests
	@printf '[\e[0;36mINFO\e[0m] Executing with all flags...\n'

commit:	# commitgs main
	@printf '[\e[0;36mINFO\e[0m] Adding main...\n'
	git add main.c
	@printf '[\e[0;36mINFO\e[0m] Commiting main...\n'
	git commit -m '[INFO] automated commit [INFO]'
	@printf '[\e[0;36mINFO\e[0m] Pushing main...\n'
	git push

