#include <snafuENG.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static void	snf_rawmode(void)
{
	static int				saved = 0;
	static struct termios	old;
	struct termios			new;

	if (saved)
		new = old;
	else
	{
		saved = 1;
		if (tcgetattr(STDIN_FILENO, &old))
			snf_error(__func__, true);
		new = old;
		new.c_cflag |= (CS8);
		new.c_iflag &= ~(BRKINT | INPCK | ISTRIP | IXON | OPOST);
		new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		new.c_cc[VMIN] = 0;
		new.c_cc[VTIME] = 100;
	}
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new))
		snf_error(__func__, true);
}

void		snf_init(void)
{
	static int init = 0;

	if (!isatty(STDIN_FILENO))
		snf_error(__func__, true);
	else if (!init)
	{
		init = 1;
		snf_rawmode();
		atexit(snf_rawmode);
	}
}
