#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#define MAX_LINE 80 // 允许的最大命令长度

struct termios orig_termios;

// 设置终端为原始模式
void set_raw_mode() {
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // 关闭回显和规范模式
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// 恢复终端的原始模式
void reset_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// 读取用户输入的命令
void read_command(char *command) {
    int index = 0;
    char c;

    printf("mysh> ");
    fflush(stdout);

    while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n') {
        if (c == 127 || c == '\b') { // 处理 Backspace 键
            if (index > 0) {
                index--;
                printf("\b \b"); // 在终端上删除一个字符
                fflush(stdout);
            }
        } else if (index < MAX_LINE - 1) {
            command[index++] = c;
            putchar(c);
            fflush(stdout);
        }
    }
    command[index] = '\0';
    putchar('\n');
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

// 注册重置终端模式函数
void exit_shell() {
    reset_raw_mode();
}

int main() {
    char command[MAX_LINE];

    // 获取并保存当前终端设置
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(exit_shell);  // 注册重置终端模式的函数

    // 设置终端为原始模式
    set_raw_mode();

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

