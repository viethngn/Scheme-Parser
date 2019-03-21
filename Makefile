#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "scheme," which just takes a line of input and
#breaks it up into tokens.

scheme: main.o lexer.o parser.o eval.o
	gcc -o scheme main.o lexer.o parser.o eval.o

main.o: main.c
	gcc -c main.c

lexer.o: lexer.c
	gcc -c lexer.c

parser.o: parser.c
	gcc -c parser.c

eval.o: eval.c
	gcc -c eval.c

clean:
	rm -f *~ *.o *.a

#^^^^^^This space must be a TAB!!.
