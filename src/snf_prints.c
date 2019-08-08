#include <ctype.h>
#include <snafuENG.h>
#include <string.h>
#include <unistd.h>

void snf_prints(const char *s, clock_t dt)
{
	clock_t	t;
	int		i;

	dt *= 1000;
	while (*s)
	{
		write(STDIN_FILENO, s++, 1);
		t = dt + clock();
		while (clock() < t)
			if (snf_getc())
			{
				write(STDIN_FILENO, s, strlen(s));
				return ;
			}
		i = 0;
		while (isspace(s[i]))
			i++;
		write(STDIN_FILENO, s, i);
		s += i;

	}
}
