#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

bool	snf_kbhit(void)
{
	int				len;
	struct termios	old;
	struct termios	new;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	ioctl(STDIN_FILENO, FIONREAD, &len);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (len != 0);
}
