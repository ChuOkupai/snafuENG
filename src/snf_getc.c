#include <ctype.h>
#include <errno.h>
#include <snafuENG.h>
#include <unistd.h>

int	snf_getc(void)
{
	unsigned char b[3];
	unsigned char c;

	if (read(STDIN_FILENO, &c, 1) < 0)
	{
		if (errno != EAGAIN)
			snf_error(__func__, true);
		return (errno = 0); // nothing to read
	}
	if (c == 27 && read(STDIN_FILENO, b, 1) > 0
		&& read(STDIN_FILENO, b + 1, 1) > 0)
	{
		if (*b == '[') //handle escapes codes
		{
			if (isdigit(b[1]))
			{
				if (read(STDIN_FILENO, b + 2, 1) > 0 && b[2] == '~')
				{
					if (b[1] > '0' && b[1] < '7')
						return (b[1] + SNFKEY_HOME - '1');
					if (b[1] == '7') return (SNFKEY_HOME);
					if (b[1] == '8') return (SNFKEY_END);
				}
				c = 0;
			}
			else
			{
				if (b[1] >= 'A' && b[1] < 'E')
					return (b[1] + SNFKEY_ARROW_UP - 'A');
				*b = 'O';
			}
		}
		if (*b == 'O')
		{
			if (b[1] == 'H') return (SNFKEY_HOME);
			if (b[1] == 'F') return (SNFKEY_END);
			c = 0;
		}
	}
	return ((c > 127) ? 0 : c);
}