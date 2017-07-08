all: sinh.o longtest quicktestspeed quicktesterror quicktestboth longtestboth incrementtestboth selecttest errortest

test: test.c
	gcc -std=c11 -m64 -o test test.c sinh.o -lm
longtest: longtest.c
	gcc -std=c11 -m64 -o longtest longtest.c sinh.o -lm
quicktestspeed: quicktestspeed.c
	gcc -std=c11 -m64 -o quicktestspeed quicktestspeed.c functions.c -lm
quicktesterror: quicktesterror.c
	gcc -std=c11 -m64 -o quicktesterror quicktesterror.c functions.c -lm
quicktestboth: quicktestboth.c
	gcc -std=c11 -m64 -o quicktestboth quicktestboth.c functions.c -lm
longtestboth: longtestboth.c
	gcc -std=c11 -m64 -o longtestboth longtestboth.c functions.c -lm
incrementtestboth: incrementtestboth.c
	gcc -std=c11 -m64 -o incrementtestboth incrementtestboth.c functions.c -lm
selecttest: selecttest.c
	gcc -std=c11 -m64 -o selecttest selecttest.c functions.c -lm
errortest: errortest.c
	gcc -std=c11 -m64 -o errortest errortest.c functions.c -lm
clean:
	rm sinh.o test longtest
sinh.o: sinh.asm
	nasm -f elf64 -o sinh.o sinh.asm
