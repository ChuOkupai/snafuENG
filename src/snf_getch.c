#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int	snf_getch(void)
{
	struct termios old, new;
	int c;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (c);
}
