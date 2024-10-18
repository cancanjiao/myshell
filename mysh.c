#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 // 允许的最大命令长度

// 读取用户输入的命令
void read_command(char *command) {
    // 打印提示符
    printf("mysh> ");
    fflush(stdout);

    // 读取输入命令
    if (fgets(command, MAX_LINE, stdin) == NULL) {
        printf("\n");
        exit(0);
    }

    // 移除换行符
    command[strcspn(command, "\n")] = '\0';
}

// 执行用户输入的命令
void execute_command(char *command) {
    pid_t pid = fork(); // 创建子进程
    if (pid == 0) {
        // 子进程执行
        char *args[MAX_LINE / 2 + 1]; // 最多支持的参数数
        int i = 0;

        // 拆分命令和参数
        args[i] = strtok(command, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        // 将各个命令名映射到各自可执行程序
        if (strcmp(args[0], "ls") == 0 || strcmp(args[0], "echo") == 0 ||
            strcmp(args[0], "cat") == 0 || strcmp(args[0], "mkdir") == 0 ||
            strcmp(args[0], "rm") == 0 || strcmp(args[0], "pwd") == 0 ||
            strcmp(args[0], "wc") == 0) {
            char exec_path[100];
            snprintf(exec_path, sizeof(exec_path), "./my%s", args[0]);
            execvp(exec_path, args);
        } else {
            printf("Unknown command: %s\n", args[0]);
        }
        exit(1);
    } else if (pid > 0) {
        // 父进程等待子进程结束
        wait(NULL);
    } else {
        // fork失败处理
        perror("fork");
    }
}

int main() {
    char command[MAX_LINE];

    // 主循环，不断读取和执行命令
    while (1) {
        read_command(command);

        // 解析和执行命令
        if (strcmp(command, "exit") == 0) {
            break; // 退出shell
        } else if (strncmp(command, "cd ", 3) == 0) {
            // 处理内置的cd命令
            if (chdir(command + 3) != 0) {
                perror("chdir");
            }
        } else {
            // 执行其他命令
            execute_command(command);
        }
    }

    return 0;
}

