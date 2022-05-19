#include "shell.h"

int main()
{
   
    while (1)
    {
        /* Print the command prompt */
        printf("$> ");
        fflush(NULL);

        /* Read a command line */
        if (!_getline(char **lineptr, size_t *n, FILE *stream))
            return 0;

        int input = 0;
        int first = 1;

        char *cmd = line;
        char *next = strchr(cmd, '|'); /* Find first '|' */

        while (next != NULL)
        {
            /* 'next' points to '|' */
            *next = '\0';
            input = run(cmd, input, first, 0);

            cmd = next + 1;
            next = strchr(cmd, '|'); /* Find next '|' */
            first = 0;
        }
        input = run(cmd, input, first, 1);
        cleanup(n);
        n = 0;
    }
    return 0;
}

static void split(char *cmd);

static int run(char *cmd, int input, int first, int last)
{
    split(cmd);
    if (args[0] != NULL)
    {
        if (strcmp(args[0], "exit") == 0)
            exit(0);
        n += 1;
        return command(input, first, last);
    }
    return 0;
}

static char *skipwhite(char *s)
{
    while (isspace(*s))
        ++s;
    return s;
}

static void split(char *cmd)
{
    cmd = skipwhite(cmd);
    char *next = strchr(cmd, ' ');
    int i = 0;

    while (next != NULL)
    {
        next[0] = '\0';
        args[i] = cmd;
        ++i;
        cmd = skipwhite(next + 1);
        next = strchr(cmd, ' ');
    }

    if (cmd[0] != '\0')
    {
        args[i] = cmd;
        next = strchr(cmd, '\n');
        next[0] = '\0';
        ++i;
    }

    args[i] = NULL;
}