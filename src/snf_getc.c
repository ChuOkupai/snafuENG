#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <snafuENG.h>
#include <unistd.h>

int			snf_getc(void)
{
	int				fd;
	unsigned char	b[3];
	unsigned int	c;


	fd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, fd | O_NONBLOCK);
	if (read(STDIN_FILENO, &c, 1) < 0)
	{
		if (errno != EAGAIN)
			snf_error(__func__, true);
		c = (errno = 0); // nothing to read
	}
	if (c == 27) //handle escapes codes
	{
		if (read(STDIN_FILENO, b, 1) < 1
			|| read(STDIN_FILENO, b + 1, 1) < 1)
			*b = 0;
		if (*b == '[')
		{
			if (isdigit(b[1]))
			{
				if (read(STDIN_FILENO, b + 2, 1) > 0 && b[2] == '~')
				{
					if (b[1] > '0' && b[1] < '7')
						c = b[1] + SNFKEY_HOME - '1';
					else if (b[1] == '7') c = SNFKEY_HOME;
					else if (b[1] == '8') c = SNFKEY_END;
				}
			}
			else if (b[1] >= 'A' && b[1] < 'E')
				c = b[1] + SNFKEY_ARROW_UP - 'A';
			else
				*b = 'O';
		}
		if (*b == 'O')
		{
			if (b[1] == 'H') c = SNFKEY_HOME;
			else if (b[1] == 'F') c = SNFKEY_END;
		}
	}
	else if (c > 127)
		c = 0;
	fcntl(STDIN_FILENO, F_SETFL, fd);
	return (c);
}