#include <snafuENG.h>
#include <stdio.h>

bool	snf_isarrow(void)
{
	int c;

	if ((c = snf_getch()) == 27)
	{
		if ((c = snf_getch()) == 91)
		{
			if ((c = snf_getch()) < SNF_ARROW_UP || c > SNF_ARROW_LEFT)
				c = 0;
			ungetc(c, stdin);
			return (c);
		}
		c = 0;
	}
	ungetc(c, stdin);
	return (0);
}
