#include "codexion.h"

static void	init_dongles(t_dongle *dongles, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
        pthread_mutex_init(&dongles[i].mutex, NULL);
        pthread_cond_init(&dongles[i].cond, NULL);
        dongles[i].in_use = 0;
        dongles[i].cooldown = 0;
		i++;
	}
}

static void	init_coders(t_coder *coders, t_dongle *dongles, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
        coders[i].id = i + 1;
        coders[i].right = &dongles[i];
        coders[i].left = &dongles[(i - 1 + n) % n];
        coders[i].last_compile_start = 0;
        coders[i].compiles_done = 0;
		i++;
	}
}

int	create_data(t_data *data, t_params *params)
{
	int	n;

	n = params->num_coders;
	data->params = *params;
	data->dongles = malloc(sizeof(t_dongle) * n);
	if (!data->dongles)
		return (0);
	data->coders = malloc(sizeof(t_coder) * n);
	if (!data->coders)
		return (free(data->dongles), 0);
	init_dongles(data->dongles, n);
	init_coders(data->coders, data->dongles, n);
	return (1);
}