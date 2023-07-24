.PHONY: all debug build clean

all: debug

install: build

debug:
	@echo "Compiling Wisp in debug mode"
	ls *.c | awk -F. '{ print $$1}' | xargs -I dot gcc dot.c -ggdb -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -std=c99 -lmpc_parser -ledit -o debug/dot

build:
	@echo "Compiling Wisp in release mode"
	 ls *.c | awk -F. '{ print $$1}' | xargs -I dot gcc dot -O2 -DNDEBUG -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -std=c99 -lmpc_parser -ledit -o target/dot
clean:
	@echo "Cleaning debug files"
	rm debug/*
