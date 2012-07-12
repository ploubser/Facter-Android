#include "hostname.h"

void get_fact(char *value)
{
    int result;
    result = gethostname(value, BUFSIZ);
    
    if(result == -1)
    {
        fprintf(stderr, "Could not retrieve fact : hostname");
        exit(1);
    }
}
