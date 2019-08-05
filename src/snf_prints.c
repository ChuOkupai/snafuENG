#include <snafuENG.h>
#include <stdio.h>

void snf_prints(const char *s, clock_t dt)
{
	clock_t t;

	dt *= 1000;
	while (*s)
	{
		putchar(*s++);
		t = dt + clock();
		while (clock() < t)
			if (snf_kbhit() && snf_getch() == '\n')
			{
				printf("%s", s);
				return ;
			}
	}
}
