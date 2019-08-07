#include <snafuENG.h>
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	snf_init();
	snf_clear();
	snf_cursor(false);
	snf_prints("Your interrupt key doesn't work lol\n", 80);
	snf_cursor(true);
	snf_delay(1000);
	snf_prints("Press a key\n", 80);
	snf_getc();
	return (0);
}
