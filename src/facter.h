#ifndef FACTER_H
#define FACTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

#ifdef W_RUBY
#include <ruby.h>
void* lookup_ruby(char*, char*);
#endif

#ifdef W_LUA
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
void* lookup_lua(char*, char*);
#endif

#define SUCCESS 1
#define FAILURE 0

#define PLUGIN_PATH "/home/psy/Facter-Android/plugins/"

typedef struct _fact
{
  // Fact name that was looked up
  char *name;
  // Returned result from fact lookup
  char *value;
  // Result code of fact lookup
  int code;
} _fact;

/* Facter lookup definitions
 * Lookups are defined on a per language basis
 */

void fact_list(char [100][BUFSIZ], int*);
void* lookup_all(char [100][BUFSIZ]);
_fact** facter_to_hash(int*);
_fact* lookup(char*);

void* lookup_c(char*, char*);
#endif
