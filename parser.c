#include "codexion.h"

static int	positive(const char *s)
{
    int i;

    i = 0;
    if (!s[0] || !s)
        return (0);
    while (s[i] != '\0')
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
	return (1);
}

long	parse_long(const char *s, int *ok)
{
    if (!positive(s))
    {
        *ok = 0;
        return (0);
    }
    *ok = 1;
    return(atoi(s));
}

int	parser(int ac, char **av, t_params *params)
{
    if (ac == 9)
    {
        if (!parse_av1_2(av, params))
            return (0);
        if (!parse_av3_4(av, params))
            return (0);
        if (!parse_av5_6(av, params))
            return (0);
        if (!parse_av7_8(av, params))
            return (0);
        return (1);
    }
    else
    {
        printf("Error: expected 8 arguments\n");
        return (0);
    }
}