#include "minishell.h"

char *ft_strncpy(char *dest , char *src, size_t n)
{
    size_t i;

    i = 0;
    while (src && src[i] && i < n)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
