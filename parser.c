#include "codexion.h"

static int	positive(const char *s)
{
    if(atoi(s))
        return (1);
	return (0);
}

static long	parse_long(const char *s, int *ok)
{
    long long a;
    if (a = positive(s))
        ok = 1;
    else
        ok = 0;
    return (ok);
}

/*
** TODO:
** 1. check argc == 9 (program name + 8 arguments)
** 2. parse argv[1] to argv[7] as numbers with ft_parse_long()
** 3. check argv[8] is exactly "fifo" or "edf" (strcmp)
** 4. fill params with the parsed values
** 5. on any error, print a clear message to stderr and return 0
** 6. return 1 if everything is valid
*/
int	parse_args(int ac, char **av, t_params *params)
{
    int i;
    if (ac == 9)
    {
        i = 0;
        if (i <= 9)
        {
            while(parse_long(av[i]) == 1)
            {
                
            }
            i++;
        }

    }
	return (0);
}