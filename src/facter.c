#include "facter.h"

_fact* lookup(char *fact)
{

  FILE *file;
  char filepath[BUFSIZ];
  void* result = NULL;

  /* This Sucks
   * TODO : Make it not suck in a C way.
   */
  sprintf(filepath, "%slibc%s.so", PLUGIN_PATH, fact);

  if((file = fopen(filepath, "r")))
    result = lookup_c(fact, filepath);
  else
  {
     sprintf(filepath, "%s%s.rb", PLUGIN_PATH, fact);

      if((file = fopen(filepath, "r")))
        result = lookup_ruby(fact, filepath);
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

  return f;
}

void* lookup_lua(char *fact, char *filepath);
