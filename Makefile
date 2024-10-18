CC=gcc

all: mysh myls myecho mycat mymkdir myrm mycd mypwd mywc

mysh: mysh.c
    $(CC) -o mysh mysh.c

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

mycd: mycd.c
    $(CC) -o mycd mycd.c

mypwd: mypwd.c
    $(CC) -o mypwd mypwd.c

mywc: mywc.c
    $(CC) -o mywc mywc.c

clean:
    rm -f mysh myls myecho mycat mymkdir myrm mycd mypwd mywc

