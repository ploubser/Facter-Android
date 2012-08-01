#include "facter.h"


void fact_list(char facts[100][BUFSIZ], int * fact_count)
{
  DIR *plugin_dir;
  struct dirent *ent;
  plugin_dir = opendir(PLUGIN_PATH);

  if(plugin_dir != NULL)
  {
    while((ent = readdir(plugin_dir)) != NULL)
    {
      if( (strcmp(ent->d_name, ".") != 0 && (strcmp(ent->d_name, "..")) != 0))
      {
        if(ent->d_name[strlen(ent->d_name) - 1] == 'o')
        {
          strncpy(facts[*fact_count], ent->d_name, strlen(ent->d_name) -3);
          *fact_count += 1;
        } 
        else if(ent->d_name[strlen(ent->d_name) - 1] == 'b')
        {
          strncpy(facts[*fact_count], ent->d_name, strlen(ent->d_name) -3);
          *fact_count += 1;
        } 
        else if(ent->d_name[strlen(ent->d_name) - 1] == 'a')
        {
          strncpy(facts[*fact_count], ent->d_name, strlen(ent->d_name) -4);
          *fact_count += 1;
        } 
      }
    }
  }
  else
  {
    fprintf(stderr, "plugin directory does not exist\n");
    exit(1);
  }
}

_fact** facter_to_hash(int *fact_count)
{
  *fact_count = 0;
  char facts[100][BUFSIZ];
  fact_list(facts, fact_count);
  static _fact **fact_results;

  for(int i = 0; i < *fact_count; i++)
  {
    fact_results = realloc(fact_results, sizeof(fact_results) + sizeof(_fact));
    fact_results[i] = lookup(facts[i]);
  }
  return fact_results;
}

_fact* lookup(char *fact)
{
  FILE *file;
  char filepath[BUFSIZ];
  void* result = NULL;

  /* This Sucks
   * TODO : Make it not suck in a C way.
   */
  sprintf(filepath, "%s%s.so", PLUGIN_PATH, fact);

  if((file = fopen(filepath, "r")))
    result = lookup_c(fact, filepath);
  else
  {
     sprintf(filepath, "%s%s.rb", PLUGIN_PATH, fact);

      if((file = fopen(filepath, "r")))
        result = lookup_ruby(fact, filepath);
      else
      {
        sprintf(filepath, "%s%s.lua", PLUGIN_PATH, fact);
        if((file = fopen(filepath, "r")))
        {
          result = lookup_lua(fact, filepath);
        }
      }
  }

  if(file)
    fclose(file);

  if(result == NULL)
  {
    result = malloc(sizeof(_fact));
    ((_fact*)result)->code = FAILURE;
    return ((_fact*)result);
  }
  else
  {
    ((_fact*)result)->code = SUCCESS;
    return ((_fact*)result);
  }
}

void* lookup_c(char *fact, char *filepath)
{
  void (*fn)(char *);
  void *lib_handle;
  char *error;
  char result[BUFSIZ];
  _fact *f;

  f = malloc(sizeof(_fact));

  lib_handle = dlopen(filepath, RTLD_LAZY);

  if(!lib_handle)
    return NULL;

  fn = dlsym(lib_handle, "get_fact");

  if( (error = dlerror()) != NULL)
  {
    return NULL;
  }

  (*fn)(result);
  dlclose(lib_handle);

  f->name = fact;
  f->value = result;

  return f;
}

void* lookup_ruby(char *fact, char *filepath)
{
  VALUE result;
  char *lookup_result;

  _fact *f;
  f = malloc(sizeof(_fact));

  ruby_init();
  rb_require(filepath);

  VALUE facter_object = rb_class_new_instance(0, NULL, rb_const_get(rb_cObject, rb_intern("Facter")));
  result = rb_funcall(facter_object, rb_intern("get_fact"), 0);
  lookup_result = RSTRING(result)->ptr;

  f->name = fact;
  f->value = lookup_result;
  ruby_finalize();

  return f;
}

void* lookup_lua(char *fact, char *filepath)
{
  lua_State *state;
  char * result;
  _fact *f;

  state = lua_open();

  luaL_openlibs(state);
  luaL_dofile(state, filepath);

  lua_getglobal(state, "get_fact");

  if(lua_type(state, -1) != LUA_TFUNCTION)
  {
    lua_pop(state, 1);
    lua_close(state);
    return NULL;
  }

  lua_pcall(state, 0, 1, 0);
  result = lua_tostring(state, 1);

  if(result)
  {
    f = malloc(sizeof(_fact));
    f->name = fact;
    f->value = result;
  }
  else
  {
    lua_pop(state, 1);
    lua_close(state);
    return NULL;
  }

  lua_pop(state, 1);
  lua_close(state);

  return f;

}
