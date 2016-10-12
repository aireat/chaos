#include "chaos.h"
#include "stdio.h"

VOID _port_log_printf(CONST CHAR *p_class, CONST CHAR *p_format, ...)
{
    va_list     args;
    INT         size;
    char        temp[96];

    size = 0;

    // add class
    {
        size += sprintf(&temp[size], " %8s", (char*)p_class);
    }

    // add message
    {
        va_start(args, p_format);

        size += vsnprintf(&temp[size], (sizeof(temp)-(size+2)), (char*)p_format, args);
        temp[size++] = 0x0D;
        temp[size]   = 0x00;

        va_end(args);
    }

    printf("%s", temp);
}