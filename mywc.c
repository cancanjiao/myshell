#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: wc <filename>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    int lines = 0, words = 0, chars = 0;
    char ch;
    
    // 读取文件内容并统计行数、单词数和字符数
    while ((ch = fgetc(file)) != EOF) {
        chars++;
        if (ch == ' ' || ch == '\n')
            words++;
        if (ch == '\n')
            lines++;
    }

    // 输出统计结果，并添加单位
    printf("%d lines, %d words, %d characters in '%s'\n", lines, words, chars, argv[1]);
    
    fclose(file);
    return 0;  // 返回成功状态
}

