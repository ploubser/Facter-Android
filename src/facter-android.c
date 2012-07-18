#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

/* TODO : Fix this hackity hack */

#define PREFIX  "libc"
#define POSTFIX  ".so"
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

void call_plugin(char *lib_file, char *result, char *plugin_name)
{
    void (*fn)(char *);
    void *lib_handle;
    char *error;
    lib_handle = dlopen(lib_file, RTLD_LAZY);

    if(!lib_handle)
    {
        fprintf(stderr, "Cannot load fact plugin : %s\n", plugin_name);
        exit(1);
    }

    fn = dlsym(lib_handle, "get_fact");

    if((error = dlerror()) != NULL)
    {
        fprintf(stderr, "Function 'get_fact' is not defined in plugin %s\n", plugin_name);
        exit(1);
    }

    (*fn)(result);
    dlclose(lib_handle);
}

int main(int argc, char *argv[])
{
    char result[BUFSIZ];
    char lib_file[] = "/home/psy/Facter-Android/plugins/libc";

    if(argc > 1)
    {
        strcat(lib_file, argv[1]);
        strcat(lib_file, ".so");

        call_plugin(lib_file, result, argv[0]);

        printf("%s\n", result);

    }
    else
    {
        DIR *plugin_dir;
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
                    call_plugin(file, result, fact);
                    printf("%s => %s\n", fact, result);
                }
            }
            closedir (plugin_dir);
        }
        else
        {
            fprintf(stderr, "plugin directory does not exist\n");
            exit(1);
        }
    }

    return 0;
}
