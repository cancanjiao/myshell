#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

void
list_directory_brief (const char *path)
{
  DIR *dir;
  struct dirent *entry;

  dir = opendir (path);
  if (dir == NULL)
    {
      perror ("opendir");
      return;
    }

  while ((entry = readdir (dir)) != NULL)
    {
      if (strcmp (entry->d_name, ".") == 0
	  || strcmp (entry->d_name, "..") == 0)
	{
	  continue;
	}
      printf ("%s\n", entry->d_name);
    }

  closedir (dir);
}

void
list_directory_long (const char *path)
{
  DIR *dir;
  struct dirent *entry;
  struct stat statbuf;
  char filepath[BUFFER_SIZE];
  char timestr[64];
  struct tm *tm_info;

  dir = opendir (path);
  if (dir == NULL)
    {
      perror ("opendir");
      return;
    }

  while ((entry = readdir (dir)) != NULL)
    {
      if (strcmp (entry->d_name, ".") == 0
	  || strcmp (entry->d_name, "..") == 0)
	{
	  continue;
	}

      snprintf (filepath, BUFFER_SIZE, "%s/%s", path, entry->d_name);

      if (lstat (filepath, &statbuf) != 0)
	{
	  perror ("lstat");
	  continue;
	}

      tm_info = localtime (&statbuf.st_mtime);
      strftime (timestr, sizeof (timestr), "%Y-%m-%d %H:%M:%S", tm_info);

      printf ("%s %u %s %s %10ld %s %s\n",
	      (S_ISDIR (statbuf.st_mode)) ? "d" : "-",
	      statbuf.st_mode & 0777,
	      (getpwuid (statbuf.st_uid))->pw_name,
	      (getgrgid (statbuf.st_gid))->gr_name,
	      statbuf.st_size, timestr, entry->d_name);
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
