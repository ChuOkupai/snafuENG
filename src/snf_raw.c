#include <snafuENG.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

void	snf_raw(bool enable)
{
	static bool				saved = 0;
	static struct termios	old;
	struct termios			new;

	if (!(enable ^ saved))
		return ;
	if (saved)
		new = old;
	else
	{
		if (tcgetattr(STDIN_FILENO, &old)) 
			snf_error(__func__, true);
		new = old;
		new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
		new.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	}
	saved = !saved;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new))
		snf_error(__func__, true);
}
