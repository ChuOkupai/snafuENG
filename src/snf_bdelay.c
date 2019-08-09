#include <snafuENG.h>

int	snf_bdelay(clock_t ms)
{
	int c;

	ms = CLOCKS_PER_SEC * ms / 1000 + clock();
	while (clock() < ms)
		if ((c = snf_getc()))
			break;
	return (c);
}
