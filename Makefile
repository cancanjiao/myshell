CC=gcc

all: myls myecho mycat mymkdir myrm  mypwd mywc 2220223125_mysh

2220223125_mysh: mysh.o mycd.o
	$(CC) -o 2220223125_mysh mysh.o mycd.o

mysh.o: mysh.c
	$(CC) -c mysh.c

mycd.o: mycd.c
	$(CC) -c mycd.c

myls: myls.c
	$(CC) -o myls myls.c

myecho: myecho.c
	$(CC) -o myecho myecho.c

mycat: mycat.c
	$(CC) -o mycat mycat.c

mymkdir: mymkdir.c
	$(CC) -o mymkdir mymkdir.c

myrm: myrm.c
	$(CC) -o myrm myrm.c

mypwd: mypwd.c
	$(CC) -o mypwd mypwd.c

mywc: mywc.c
	$(CC) -o mywc mywc.c
clean:
	rm -f *.o 2220223125_mysh myls myecho mycat mymkdir myrm mypwd mywc
