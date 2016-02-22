ODIR = bin
   dummy_build_folder := $(shell mkdir -p $(ODIR))

main.o : src/main.c
	gcc -std=c99 -Wall -Wextra src/main.c -lm -o bin/simulation