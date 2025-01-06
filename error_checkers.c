#include "solong.h"

void	initial_check(int args, int map_check, char *error)
{
	if (args != 2)
	{
		perror("Bad program arguments");
		exit(1);
	}
	if (!map_check)
	{
		perror(error);
		exit(0);
	}
}