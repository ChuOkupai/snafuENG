#include <snafuENG.h>
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int c;

	snf_clear();
	printf("Press enter to continue...\n");
	while (snf_getch() != '\n');
	snf_clear();
	printf("Waiting 2,75s...\n");
	snf_delay(1250);
	snf_clear();
	snf_prints("Hello, World!\n", 300);
	snf_prints("This is a test.\n", 150);
	snf_prints("I repeat, this is a test.\n", 75);
	snf_prints("Now press a key.\n", 50);
	while (!snf_kbhit());
	if (snf_isarrow())
		printf("> it's an arrow key!\n");
	else if (!isprint((c = snf_getch())))
		printf("> cannot display this key!\n");
	else
		printf("> key pressed: '%c'\n", c);
	return (0);
}
