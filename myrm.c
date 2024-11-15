#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    // 检查是否提供了文件名
    if (argc < 2) {
        printf("Usage: rm <filename>\n");
        return 1;
    }

    // 删除文件
    if (unlink(argv[1]) == -1) {
        perror("unlink");
        return 1;
    }

    return 0;  // 返回成功状态
}

