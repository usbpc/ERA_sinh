objects = sinh.o functions.o

all: sinh.o longtest quicktestspeed quicktesterror quicktestboth longtestboth incrementtestboth selecttest errortest

test: test.c
	gcc -std=c11 -m64 -o test test.c sinh.o -lm
longtest: longtest.c
	gcc -std=c11 -m64 -o longtest longtest.c sinh.o -lm
quicktestspeed: quicktestspeed.c $(objects)
	gcc -std=c11 -m64 -o quicktestspeed quicktestspeed.c $(objects) -lm
quicktesterror: quicktesterror.c $(objects)
	gcc -std=c11 -m64 -o quicktesterror quicktesterror.c $(objects) -lm
quicktestboth: quicktestboth.c $(objects)
	gcc -std=c11 -m64 -o quicktestboth quicktestboth.c $(objects) -lm
longtestboth: longtestboth.c $(objects)
	gcc -std=c11 -m64 -o longtestboth longtestboth.c $(objects) -lm
incrementtestboth: incrementtestboth.c $(objects)
	gcc -std=c11 -m64 -o incrementtestboth incrementtestboth.c $(objects) -lm
selecttest: selecttest.c $(objects)
	gcc -std=c11 -m64 -o selecttest selecttest.c $(objects) -lm
errortest: errortest.c $(objects)
	gcc -std=c11 -m64 -o errortest errortest.c $(objects) -lm
functions.o: functions.c
	gcc -std=c11 -m64 -c functions.c
clean:
	rm sinh.o test longtest
sinh.o: sinh.asm
	nasm -f elf64 -o sinh.o sinh.asm
