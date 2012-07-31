#include "timezone.h"

int get_fact(char *value)
{
   time_t now = time(NULL);
   struct tm tnow = *gmtime(&now);

   if(tm == NULL)
     return 1;

   strftime(value, BUFSIZ, "%Z", &tnow);

   //Think about some exception handling
   return 0;
}
