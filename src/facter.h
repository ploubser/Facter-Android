#ifndef FACTER_H
#define FACTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

//IFDEF RUBY
#include <ruby.h>

//IFDEF LUA
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define SUCCESS 1
#define FAILURE 0

#define C_PREAMBLE "libc"
#define C_POSTAMBLE ".so"
#define RUBY_POSTAMBLE ".rb"
#define LUA_POSTAMBLE ".lua"
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
 *
 * TODO: LUA
 */

_fact* lookup(char*);
void* lookup_c(char*, char*);
void* lookup_ruby(char*, char*);
void* lookup_lua(char*, char*);
#endif
