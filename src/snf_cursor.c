#include <stdbool.h>
#include <unistd.h>

void	snf_cursor(bool show)
{
	write(STDIN_FILENO, (show) ? "\e[?25h" : "\e[?25l", 6);
}
