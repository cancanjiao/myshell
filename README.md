# myshell
实验：
自己编写一个简单的shell

run:

make clean

make

./mysh

exit:(input in mysh)

exit 


实验二： Linux 命令环境下 C/C++语言实践
1. 实验目的
 用 C/C++构造一个简单的 shell；
 理解 shell 程序的功能；
 加深 shell 的使用；
 掌握基本的 makefile 方法。

2. 实验内容
 基本任务 1：用 C/C++编写一个简单的 shell 程序，实现以下基本的命令。
(1) 浏览目录和文件的各种属性 ls 及 ls -l（可以不支持其他参数）
(2) 回显命令 echo
(3) 显示文件内容 cat
(4) 创建目录 mkdir
(5) 删除文件 rm
(6) 切换目录 cd
(7) 显示当前目录 pwd
(8) 文字统计 wc

 基本任务 2：每一条命令单独对应一个源程序文件，不允许所有命令写在单
独一个文件。

 基本任务 3：写一个 makefile 来管理源代码，并写清楚 make 编译和运行的
过程。

 选做任务
 任何你想实现的其它命令。
 提供友好的人机界面：例如提供命令列表、命令查询、命令帮助等。

 Advanced shell 功能：
(1) 输入输出重定向，例如：./a.out > output.txt
(2) 支持多管道命令，例如：./a.out | ./b.out | ./c.out
(3) 支持后台运行命令，例如：ls | wc &
(4) 其它：参考 GNU bash 提供的功能。

 参考程序：
 man 手册，例如：
(1) man 2 stat //获取文件数据结构；
(2) man readdir //获取目录数据结构
 网上资源

3. 实验要求
 独立完成实验内容
 良好的编程风格
 注意事项
 禁止使用 system/exec 等函数直接调用系统 shell 提供的内在命令。
 如果需要执行指定的程序，可以使用 fork 函数生成一个新进程执行。
