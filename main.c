#include "shell.h"

/**
 * main - entry point
 * @av: arg vector
 * @ac: arg count
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	mereja_t mereja[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				sehetetputs(av[0]);
				sehetetputs(": 0: Can't open ");
				sehetetputs(av[1]);
				sehetetputchar('\n');
				sehetetputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		mereja->readfd = fd;
	}
	populatesehetetnv_list(mereja);
	read_tarik(mereja);
	hsh(mereja, av);
	return (EXIT_SUCCESS);
}
