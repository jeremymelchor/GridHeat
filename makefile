ODIR = bin
   dummy_build_folder := $(shell mkdir -p $(ODIR))

main.o : main.c
	gcc -std=c99 -Wall -Wextra main.c -lm -o simulation