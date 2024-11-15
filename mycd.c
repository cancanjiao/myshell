#include <stdio.h>
#include <unistd.h>
#include "mycd.h"
void mycd(int argc, char **argv) {
    // 检查是否提供了目录名称
    if (argc < 2) {
        printf("Usage: cd <directory>\n");
        return;
    }

    // 切换目录
    if (chdir(argv[1]) == -1) {
        perror("chdir");
        return;
    }

    return;  // 返回成功状态
}
