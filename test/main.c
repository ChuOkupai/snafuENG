#include <snafuENG.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int c;

	snf_init();
	snf_clear();
	snf_cursor(false);
	snf_prints("Your interrupt key doesn't work lol\n", 500);
	snf_prints("Press q to quit...\n", 200);
	snf_cursor(true);
	while ((c = snf_getc()) != 'q')
		if (snf_isarrow(c))
			printf("arrow key pressed!\n");
	return (0);
}
