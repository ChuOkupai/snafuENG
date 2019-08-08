#include <unistd.h>

void	snf_clear(void)
{
	write(STDIN_FILENO, "\e[2J\e[H\e[3J", 11);
}
