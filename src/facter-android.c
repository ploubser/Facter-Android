#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "facter.h"

#define PREFIXL  4
#define POSTFIXL 3


void clean(char *fact, char *factname)
{
  int i;
  int string_length = strlen(fact);

  for(i = PREFIXL; i < string_length - POSTFIXL; i++)
  {
    factname[i-PREFIXL] = fact[i];
    factname[i-POSTFIXL] = '\0';
  }
}

int main(int argc, char *argv[])
{
  _fact *f;
  if(argc > 1)
  {
    f = lookup(argv[1]);

    if(f->code == SUCCESS)
      printf("%s\n", f->value);

  }
  else
  {
/*    DIR *plugin_dir;
    struct dirent *ent;
    char plugin_dir_string[BUFSIZ] = "/home/psy/Facter-Android/plugins/";
    char file[BUFSIZ];
    char fact[BUFSIZ];
    plugin_dir = opendir(plugin_dir_string);

    if(plugin_dir != NULL)
    {
      while ((ent = readdir(plugin_dir)) != NULL)
      {
        if( (strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..")) )
        {
          clean(ent->d_name, fact);
          sprintf(file, "%s%s", plugin_dir_string, ent->d_name);
          printf("%s => %s\n", fact, result);
        }
      }
      result[0] = '\0';
      closedir (plugin_dir);
    }
    else
    {
      fprintf(stderr, "plugin directory does not exist\n");
      exit(1);
    }*/
  }

  return 0;
}
