#include <stdbool.h>
#include <stdio.h>

void	snf_cursor(bool show)
{
	printf((show) ? "\e[?25h" : "\e[?25l");
}
