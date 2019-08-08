#include <fcntl.h>
#include <snafuENG.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static void	snf_rawmode(void)
{
	int						fd;
	static int				saved = 0;
	static struct termios	old;
	struct termios			new;

	if (saved)
		new = old;
	else
	{
		saved = 1;
		if (tcgetattr(STDIN_FILENO, &old)
			|| (fd = fcntl(STDIN_FILENO, F_GETFL, 0)) < 0
			|| fcntl(STDIN_FILENO, F_SETFL, fd | O_NONBLOCK) < 0)
			snf_error(__func__, true);
		new = old;
		new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
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
