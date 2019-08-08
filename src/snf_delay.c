#include <time.h>

void	snf_delay(clock_t ms)
{
	ms = CLOCKS_PER_SEC * ms / 1000 + clock();
	while (clock() < ms);
}
