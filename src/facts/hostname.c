#include "hostname.h"

int get_fact(char *value)
{
    int result;
    result = gethostname(value, BUFSIZ);

    if(result == -1)
        return(1);

    return 0;
}
