#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "facter.h"

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
    int fact_count = 0;
    _fact **facts = facter_to_hash(&fact_count);

    for(int i = 0; i < fact_count; i++)
      printf("%s => %s\n", facts[i]->name, facts[i]->value);
  }

  return 0;
}
