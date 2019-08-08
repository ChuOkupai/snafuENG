#include <ctype.h>
#include <errno.h>
#include <snafuENG.h>
#include <unistd.h>

int	snf_getc(void)
{
	char b[3];
	char c;

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
					if (b[1] == '1') return (SNFKEY_HOME);
					if (b[1] == '2') return (SNFKEY_INS);
					if (b[1] == '3') return (SNFKEY_DEL);
					if (b[1] == '4') return (SNFKEY_END);
					if (b[1] == '5') return (SNFKEY_PAGE_UP);
					if (b[1] == '6') return (SNFKEY_PAGE_DOWN);
					if (b[1] == '7') return (SNFKEY_HOME);
					if (b[1] == '8') return (SNFKEY_END);
				}
			}
			else
			{
				if (b[1] == 'A') return (SNFKEY_ARROW_UP);
				if (b[1] == 'B') return (SNFKEY_ARROW_DOWN);
				if (b[1] == 'C') return (SNFKEY_ARROW_RIGHT);
				if (b[1] == 'D') return (SNFKEY_ARROW_LEFT);
				*b = 'O';
			}
		}
		if (*b == 'O')
		{
			if (b[1] == 'H') return (SNFKEY_HOME);
			if (b[1] == 'F') return (SNFKEY_END);
		}
	}
	return ((c < 0) ? 0 : c);
}