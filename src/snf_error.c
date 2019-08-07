#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	snf_error(const char *function, bool quit)
{
	if (!errno)
		return ;
	char *message;

	message = strerror(errno);
	write(STDERR_FILENO, "snafuENG: ", 10);
	write(STDERR_FILENO, function, strlen(function));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, strlen(message));
	write(STDERR_FILENO, "\n", 1);
	if (quit)
		exit(0);
	errno = 0;
}
