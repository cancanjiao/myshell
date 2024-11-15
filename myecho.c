#include <stdio.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);  // 输出每个参数
    }
    printf("\n");  // 输出换行符
    return 0;
}

