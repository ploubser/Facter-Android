#include "operatingsystem.h"

int get_fact(char *value)
{
  struct utsname utsname;
  regex_t regex;
  FILE *identity_file;
  int regex_result;

  uname(&utsname);

  if(uname == NULL)
    return 1;

  regcomp(&regex, "^Linux", 0);
  regex_result = regexec(&regex, utsname.sysname, 0, NULL, 0);

  if(!regex_result)
  {
    // More operating systems go here
    if( (identity_file = fopen("/etc/debian_version", "r")) != NULL)
      strcpy(value,"Debian");
    else if( (identity_file = fopen("/etc/centos-release", "r")) != NULL)
    {
      strcpy(value, "Centos");
    }
  }
  else
  {
    value = utsname.sysname;
  }

  return 0;
}
