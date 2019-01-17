#include <snafuENG.h>

void snf_seteng(const bool on)
{
	// + check if program is running in terminal (isatty)
	static struct termios current, save;
	static bool init = 0;

	if (! init && on)
	{
		srand(time(0));
		tcgetattr(0, &save);
		current = save;
		current.c_lflag &= ~ECHO;
		tcsetattr(0, TCSANOW, &current);
		snf_setdefcfg();
		cfg.system.cursor = 1;
		cfg.system.engine = 1;
		snf_setcur(0);
		init = 1;
	}
	else if (! on && init)
	{
		tcsetattr(0, TCSANOW, &save);
		snf_setcur(1);
		cfg.system.engine = 0;
		init = 0;
		remove(SNF_PATH_TMP);
	}
}

void snf_fexit()
{
	if (cfg.system.engine)
		snf_seteng(0);
	snf_wwarn(SNF_WARN_EXIT, 0, __func__);
	puts("Snafu was forced to quit.");
	printf("Please send your %s and %s files to the developpers :\n", SNF_PATH_DEBUG, SNF_PATH_LOG);
	puts("https://github.com/ChuOkupai/snafu");
	exit(SNF_WARN_EXIT);
}

void checkeng(const char *function)
{
	if (! cfg.system.engine)
	{
		snf_werr(SNF_ERR_ENGINE, 0, function);
		snf_wdebug();
		snf_fexit();
	}
}

void snf_clear()
{
	if (system("clear") == -1)
	{
		snf_werr(SNF_ERR_SYSTEM, 0, __func__);
		if (cfg.system.engine)
			snf_seteng(0);
		snf_fexit();
	}
}

void snf_fsleep(const float s)
{
	struct timespec	t;

	t.tv_sec = (int)s;
	t.tv_nsec = 1000000000 * (s - t.tv_sec);
	nanosleep(&t, 0);
}

int snf_randi(const int min, const int max)
{
	return (rand() % (max - min + 1)) + min;
}

int snf_kbhit()
{
	struct termios oldt, newt;
	int c, oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if (c != EOF)
	{
		ungetc(c, stdin);
		return 1;
	}
	return 0;
}

int snf_waitret()
{
	return getchar();
}

bool snf_getarrow(int *c)
{
	*c = getchar();
	if (*c == 27)
	{
		*c = getchar();
		if (*c == 91)
		{
			*c = getchar();
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}

void snf_setcur(const bool on)
{
	bool error = 0;
	
	if (! cfg.system.cursor && on)
	{
		if (system("setterm -cursor on") == -1)
			error++;
		cfg.system.cursor = 1;
	}
	else if (! on && cfg.system.cursor)
	{
		if (system("setterm -cursor off") == -1)
			error++;
		cfg.system.cursor = 0;
	}
	if (error)
	{
		snf_werr(SNF_ERR_SYSTEM, 0, __func__);
		if (cfg.system.engine)
			snf_seteng(0);
		snf_wdebug();
		snf_fexit();
	}
}