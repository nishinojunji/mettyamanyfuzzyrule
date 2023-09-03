all	: fuzzy

fuzzy	: main.o fuzzy.o
	$(CC) -o fuzzy main.o fuzzy.o

main.o	: fuzzy.h fuzzy.c main.c
fuzzy.o	: fuzzy.h fuzzy.c
