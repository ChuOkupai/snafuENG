#include <ctype.h>
#include <snafuENG.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define QUIT_MSG "Press 'q' to quit\n"

void	test_keys(void)
{
	int c;

	snf_clear();
	printf("Testing keys:\n");
	printf(QUIT_MSG);
	while ((c = snf_getc()) != 'q')
	{
		if (!c)
			continue;
		if (snf_iskeycode(c))
			printf("%s", snf_ktoa(c));
		else
		{
			printf("%d", c);
			if (isprint(c))
				printf(" → %c", c);
		}
		putchar('\n');
	}
}

void	test_print(void)
{
	snf_clear();
	snf_prints("This function is \033[38;2;255;120;250mamazing\033[0m!\n", 100);
	snf_prints("  You can \033[38;2;255;0;0mskip\033[0m the animation if you press a key.\n", 100);
	snf_prints(" It handles \033[3mspaces\033[0m and \033[4mnon printables\033[0m characters\n", 100);
	snf_prints(QUIT_MSG, 100);
	while (snf_getc() != 'q');
}

int		main(void)
{
	snf_init();
	test_print();
	test_keys();
	return (0);
}
