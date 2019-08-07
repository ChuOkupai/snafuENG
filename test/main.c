#include <snafuENG.h>
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	if (snf_init() < 0)
	{
		printf("error: snafuENG not initialized!\n");
		return (0);
	}
	snf_clear();
	snf_cursor(false);
	snf_prints("Your interrupt doesn't work lol\n", 80);
	snf_cursor(true);
	snf_delay(1000);
	snf_prints("Press a key\n", 80);
	snf_getc();
	return (0);
}
