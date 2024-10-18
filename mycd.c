#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    // 检查是否提供了目录名称
    if (argc < 2) {
        printf("Usage: cd <directory>\n");
        return 1;
    }

    // 切换目录
    if (chdir(argv[1]) == -1) {
        perror("chdir");
        return 1;
    }

    return 0;  // 返回成功状态
}

