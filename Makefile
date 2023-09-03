all	: fuzzy

fuzzy	: main.o fuzzy.o
	$(CC) -o fuzzy main.o fuzzy.o
