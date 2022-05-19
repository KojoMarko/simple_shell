#include "shell.h"

/**
 * _malloc - allocate a buffer for storing the lineptr variable for _getline.
 * @lineptr: A buffer to store an input string.
 * @n: The number of characters of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void _malloc(char **lineptr, size_t *n, char *buffer, size_t b)
{
    if (*lineptr == NULL)
    {
        if (b > 120)
            *n = b;
        else
            *n = 120;
        *lineptr = buffer;
    }
    else if (*n < b)
    {
        if (b > 120)
            *n = b;
        else
            *n = 120;
        *lineptr = buffer;
    }
    else
    {
        _strcpy(*lineptr, buffer);
        free(buffer);
    }
}
