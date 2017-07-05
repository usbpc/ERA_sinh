all: test longtest quicktestspeed quicktesterror quicktestboth

test: sinh.o test.c
	gcc -std=c11 -m64 -o test test.c sinh.o -lm
longtest: sinh.o longtest.c
	gcc -std=c11 -m64 -o longtest longtest.c sinh.o -lm
quicktestspeed: sinh.o quicktestspeed.c
	gcc -std=c11 -m64 -o quicktestspeed quicktestspeed.c sinh.o -lm
quicktesterror: sinh.o quicktesterror.c
	gcc -std=c11 -m64 -o quicktesterror quicktesterror.c sinh.o -lm
quicktestboth: sinh.o quicktestboth.c
	gcc -std=c11 -m64 -o quicktestboth quicktestboth.c sinh.o -lm
clean:
	rm sinh.o test longtest
sinh.o: sinh.asm
	nasm -f elf64 -o sinh.o sinh.asm
