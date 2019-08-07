#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static void	snf_rawmode(void)
{
	static int				saved = 0;
	static struct termios	old;
	struct termios			new;

	if (saved)
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
	else
	{
		tcgetattr(STDIN_FILENO, &old); // handle error!
		new = old;
		new.c_cflag |= (CS8);
		new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON | OPOST);
		new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		new.c_cc[VMIN] = 0;
		new.c_cc[VTIME] = 100;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &new); // handle error!
		saved = 1;
	}
}

int			snf_init(void)
{
	static int init = 0;

	if (!isatty(STDIN_FILENO))
		return (-1);
	else if (!init)
	{
		snf_rawmode();
		atexit(snf_rawmode);
		init = 1;
	}
	return (0);
}
