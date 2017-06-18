test: sinh.o
	gcc -std=c11 -m64 -o test test.c sinh.o -lm
longtest: sinh.o
	gcc -std=c11 -m64 -o longtest longtest.c sinh.o -lm
clean:
	rm sinh.o test longtest
sinh.o:
	nasm -f elf64 -o sinh.o sinh.asm
