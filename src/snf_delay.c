#include <snafuENG.h>

void	snf_delay(clock_t ms)
{
	ms = 1000 * ms + clock();
	while (clock() < ms);
}
