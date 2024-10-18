#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];
    
    // 获取当前目录
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);  // 输出当前目录
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;  // 返回成功状态
}

