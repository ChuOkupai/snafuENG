#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <snafuENG.h>
#include <unistd.h>

int			snf_getc(void)
{
	int				fd;
	unsigned char	b[4];

	if ((fd = fcntl(STDIN_FILENO, F_GETFL, 0)) < 0
		|| fcntl(STDIN_FILENO, F_SETFL, fd | O_NONBLOCK) < 0
		|| read(STDIN_FILENO, b, 4) < 0)
	{
		if (errno != EAGAIN)
			snf_error(__func__, true);
		return (errno = 0); // nothing to read
	}
	if (fcntl(STDIN_FILENO, F_SETFL, fd) < 0)
		snf_error(__func__, true);
	if (*b == 27) //handle escapes codes
	{
		if (b[1] == '[')
		{
			if (isdigit(b[2]))
			{
				if (b[3] == '~')
				{
					if (b[2] > '0' && b[2] < '7')
						return (b[2] + SNFKEY_HOME - '1');
					if (b[2] == '7') return (SNFKEY_HOME);
					if (b[2] == '8') return (SNFKEY_END);
				}
			}
			else if (b[2] >= 'A' && b[2] < 'E')
				return (b[2] + SNFKEY_ARROW_UP - 'A');
			else
				b[1] = 'O';
		}
		if (b[1] == 'O')
		{
			if (b[2] == 'H') return (SNFKEY_HOME);
			if (b[2] == 'F') return (SNFKEY_END);
		}
	}
	else if (*b > 127)
		*b = 0;
	return (*b);
}