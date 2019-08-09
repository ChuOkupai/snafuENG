#include <errno.h>
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
		if (tcgetattr(STDIN_FILENO, &old)) 
			snf_error(__func__, true);
		new = old;
		new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
		saved = 1;
	}
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new))
		snf_error(__func__, true);
}

void		snf_init(void)
{
	static int init = 0;

	if (init)
	{
		errno = ECANCELED;
		snf_error(__func__, false);
		return ;
	}
	if (!isatty(STDIN_FILENO))
		snf_error(__func__, true);
	snf_rawmode();
	atexit(snf_rawmode);
	init = 1;
}
