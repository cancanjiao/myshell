#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //目录读取库
#include <sys/types.h>//data type
#include <sys/stat.h>//queue file staus lstat()
#include <unistd.h>
#include <string.h>
//#include <errno.h>
#include <pwd.h>//getpwuid()  get usr message
#include <grp.h>//getgrgid()  get group message
#include <time.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void list_directory_brief (const char *path)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir (path);
  if (dir == NULL)
    {
      printf("opendi rerror");
      return;
    }

  while ((entry = readdir (dir)) != NULL)
    {
      if (strcmp (entry->d_name, ".") == 0|| strcmp (entry->d_name, "..") == 0)
	{
	  continue;
	}
      printf ("%s\n", entry->d_name);
    }

  closedir (dir);
}

void list_directory_long (const char *path)
{
  DIR *dir;
  struct dirent *entry; //目录结构体指针
  struct stat statbuf; //文件状态信息
  char filepath[BUFFER_SIZE]; //文件路径缓冲区
  char timestr[64]; //时间字符串缓冲区
  struct tm *tm_info;//本地时间信息指针

  dir = opendir (path);
  if (dir == NULL)
    {
      printf ("opendir  error");
      return;
    }

  while ((entry = readdir (dir)) != NULL)
    {
      if (strcmp (entry->d_name, ".") == 0
	  || strcmp (entry->d_name, "..") == 0)
	{
	  continue;
	}

      snprintf (filepath, BUFFER_SIZE, "%s/%s", path, entry->d_name);//构建文件完整路径

      if (lstat (filepath, &statbuf) != 0)
	{
	  printf ("lstat error");//获取文件状态失败
	  continue;
	}

      tm_info = localtime (&statbuf.st_mtime);//将修改时间转化成本地时间
      strftime (timestr, sizeof (timestr), "%Y-%m-%d %H:%M:%S", tm_info);//格式化时间

      printf ("%s %u %s %s %10ld %s %s\n",
	      (S_ISDIR (statbuf.st_mode)) ? "d" : "-",//判断是目录还是普通文件
	      statbuf.st_mode & 0777,//文件权限
	      (getpwuid (statbuf.st_uid))->pw_name,//文件所有者的用户
	      (getgrgid (statbuf.st_gid))->gr_name,//文件所属组的组名
	      statbuf.st_size,//文件大小
	      timestr, entry->d_name);//修改时间
    }

  closedir (dir);
}

int
main (int argc, char *argv[])
{
  const char *directory = ".";	// 默认当前目录  
  bool long_format = false;	// 默认不使用长格式  

  // 处理命令行参数  
  int opt;
  while ((opt = getopt (argc, argv, "l")) != -1)
    {
      if (opt == 'l')
	{
	  long_format = true;
	}
      else
	{
	  // 如果有未知的选项，可以打印帮助信息并退出  
	  // 这里为了简单，我们只接受'l'选项，其他都忽略  
	  fprintf (stderr, "Usage: %s [-l]\n", argv[0]);
	  exit (EXIT_FAILURE);
	}
    }

  // 如果还有额外的参数（除了-l之外），我们假设它是目录路径  
  if (optind < argc)
    {
      directory = argv[optind];
    }

  // 根据格式要求列出目录内容  
  if (long_format)
    {
      list_directory_long (directory);
    }
  else
    {
      list_directory_brief (directory);
    }

  return 0;
}
