myprogram: main.o hangman-io.o 
	clang -o myprogram main.o hangman-io.o

hangman-io.o: hangman-io.c hangman-io.h
	clang -c hangman-io.c

main.o: main.c hangman-io.h words.h
	clang -c main.c

,PHONY: clean

clean:
	rm -f *.o myprogram