#include "operatingsystem.h"

int get_fact(char *value)
{
  struct utsname utsname;
  uname(&utsname);
  FILE *identity_file;

  printf("%s", utsname.sysname);

  if(strcmp(utsname.sysname, "Linux"))
  {
    // More operating systems go here
    if( (identity_file = fopen("/etc/debian_version", "r")) != NULL)
      value = "Debian";
    else if( (identity_file = fopen("/etc/centos-release", "r")) != NULL)
      value = "Centos";
  }
  else
    value = utsname.sysname;

  return 0;
}
