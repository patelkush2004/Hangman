myprogram: main.o hangman-io.o words.o
	clang main.o hangman-io.o words.o -o myprogram 

hangman-io.o: hangman-io.c hangman-io.h
	clang -c hangman-io.c

words.o: words.c words.h
	clang -c words.c

main.o: main.c hangman-io.h words.h
	clang -c main.c

,PHONY: clean

clean:
	rm -f *.o myprogram