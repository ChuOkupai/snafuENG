#include <ctype.h>
#include <errno.h>
#include <snafuENG.h>
#include <unistd.h>

int	snf_getc(void)
{
	char c[3] = { 0 };

	*c = 0;
	if (read(STDIN_FILENO, c, 1) < 0)
	{
		if (errno == EAGAIN)
			errno = 0;
		else
			snf_error(__func__, true);
	}
	else if (*c == 27 && read(STDIN_FILENO, c, 1) > 0)
	{
		if (read(STDIN_FILENO, &c[1], 1) < 1)
			return (27);
		if (*c == '[')
		{
			if (isdigit(c[1]))
		 	{
				if (read(STDIN_FILENO, &c[2], 1) < 1)
					return (27);
				if (c[2] == '~')
				{
					switch (c[1])
					{
						case '1': return SNFKEY_HOME;
						case '3': return SNFKEY_DEL;
						case '4': return SNFKEY_END;
						case '5': return SNFKEY_PAGE_UP;
						case '6': return SNFKEY_PAGE_DOWN;
						case '7': return SNFKEY_HOME;
						case '8': return SNFKEY_END;
					}
				}
			}
			else
			{
				switch (c[1])
				{
					case 'A': return SNFKEY_ARROW_UP;
					case 'B': return SNFKEY_ARROW_DOWN;
					case 'C': return SNFKEY_ARROW_RIGHT;
					case 'D': return SNFKEY_ARROW_LEFT;
					case 'H': return SNFKEY_HOME;
					case 'F': return SNFKEY_END;
				}
			}
		}
		else if (*c == 'O')
		{
			switch (c[1])
			{
				case 'H': return SNFKEY_HOME;
				case 'F': return SNFKEY_END;
			}
		}
		return (27);
	}
	return (*c);
}