#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int	snf_kbhit(void)
{
	struct termios old, new;
	int c, oldf;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	c = getc(stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (c == EOF)
		return (0);
	ungetc(c, stdin);
	return (1);
}
