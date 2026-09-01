#include "codexion.h"

int	parse_av1_2(char **av, t_params *p)
{
	int	ok;

	p->num_coders = (int)parse_long(av[1], &ok);
	if (!ok || p->num_coders < 1)
	{
		printf("Error: invalid number_of_coders\n");
		return (0);
	}
	p->burnout = parse_long(av[2], &ok);
	if (!ok)
	{
		printf("Error: invalid time_to_burnout\n");
		return (0);
	}
	return (1);
}

int	parse_av3_4(char **av, t_params *p)
{
	int	ok;

	p->compile = parse_long(av[3], &ok);
	if (!ok)
	{
		printf("Error: invalid time_to_compile\n");
		return (0);
	}
	p->debug = parse_long(av[4], &ok);
	if (!ok)
	{
		printf("Error: invalid time_to_debug\n");
		return (0);
	}
	return (1);
}

int	parse_av5_6(char **av, t_params *p)
{
	int	ok;

	p->refactor = parse_long(av[5], &ok);
	if (!ok)
	{
		printf("Error: invalid time_to_refactor\n");
		return (0);
	}
	p->required = (int)parse_long(av[6], &ok);
	if (!ok)
	{
		printf("Error: invalid number_of_compiles_required\n");
		return (0);
	}
	return (1);
}

int	parse_av7_8(char **av, t_params *p)
{
	int	ok;

	p->cooldown = parse_long(av[7], &ok);
	if (!ok)
	{
		printf("Error: invalid dongle_cooldown\n");
		return (0);
	}
	if (strcmp(av[8], "fifo") != 0 && strcmp(av[8], "edf") != 0)
	{
		printf("Error: scheduler must be 'fifo' or 'edf'\n");
		return (0);
	}
	p->scheduler = av[8];
	return (1);
}