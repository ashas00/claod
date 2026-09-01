#include "codexion.h"

int	main(int argc, char **argv)
{
	t_params	params;

	if (!parse_args(argc, argv, &params))
		return (1);
	printf("Parsed OK: %d coders, scheduler=%s\n",
		params.num_coders, params.scheduler);
	return (0);
}