objects = sinh.o functions.o tests.o

sinhtest: src/sinhtest.c $(objects)
	gcc -std=c11 -m64 -o bin/sinhtest src/sinhtest.c $(objects) -lm
tests.o: src/tests.c src/tests.h
	gcc -std=c11 -m64 -c src/tests.c
functions.o: src/functions.c src/functions.h
	gcc -std=c11 -m64 -c src/functions.c
sinh.o: src/sinh.asm src/sinh.h
	nasm -f elf64 -o sinh.o src/sinh.asm
clean:
	rm *.o
	rm ./bin/*