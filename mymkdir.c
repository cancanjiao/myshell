#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: mkdir <dirname>\n");
        return 1;
    }

    if (mkdir(argv[1], 0777) == -1) {  // 0777表示新目录的权限
        perror("mkdir");
        return 1;
    }

    return 0;
}

