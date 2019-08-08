#include <ctype.h>
#include <snafuENG.h>
#include <string.h>
#include <unistd.h>

// TODO: detect escape sequences length (in order to skip it)
static int			snf_strlenh(const char *s)
{
	int i;

	i = 0;
	while (s[i] && (!isprint(s[i]) || isspace(s[i])))
		i++;
	return (i);
}

static const char*	snf_pmove(const char *s, int len)
{
	if (len)
		write(STDIN_FILENO, s, len);
	return (s + len);
}

void		snf_prints(const char *s, clock_t dt)
{
	int len;

	while (*s)
	{
		if (*(s = snf_pmove(s, snf_strlenh(s))))
			write(STDIN_FILENO, s++, 1);
		if (!*(s + (len = snf_strlenh(s)))) // only hidden characters left
			s = snf_pmove(s, len);
		else if (snf_bdelay(dt)) // true if user press a key
			s = snf_pmove(s, strlen(s));
	}
}
