#include "codexion.h"

/* TODO: эта функция будет "телом" потока каждого кодера.
 * Пока — просто выведи id кодера, чтобы проверить, что pthread_create работает.
 * arg приходит как void*, а реально это t_coder* — нужно привести тип. */
void	*coder_thread(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	printf("coder %d: alive\n", coder->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_data		data;
	int			i;

	if (!parser(argc, argv, &params))
		return (1);
	if (!create_data(&data, &params))
		return (1);
	i = 0;
	while (i < params.num_coders)
	{
        pthread_create(&data.coders[i].thread, NULL, coder_thread, &data.coders[i]);
		i++;
	}
	i = 0;
	while (i < params.num_coders)
	{
        pthread_join(data.coders[i].thread, NULL);
		i++;
	}
	free(data.coders);
	free(data.dongles);
	return (0);
}