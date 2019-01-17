#include <snafuENG.h>
#include <snafuENG-CFG.c>
#include <snafuENG-LOG.c>
#include <snafuENG-SYS.c>

#define TLC	0
#define TRC	1
#define LLC	2
#define LRC	3
#define HL	4
#define VL	5
const char** snf_loadhudtheme()
{
	const char **hud = (const char**)malloc(6 * sizeof(const char*));
	
	if (! hud)
	{
		snf_werr(SNF_ERR_MEMORY, 0, __func__);
		return 0;
	}
	for (int i = 0; i < 6; i++)
	{
		hud[i] = malloc(3 * sizeof(char));
		if (! hud[i])
		{
			snf_werr(SNF_ERR_MEMORY, 0, __func__);
			free(hud);
			return 0;
		}
	}
	if (cfg.hud.theme == 1)
	{
		hud[TLC] = "┌";
		hud[TRC] = "┐";
		hud[LLC] = "└";
		hud[LRC] = "┘";
		hud[HL] = "─";
		hud[VL] = "│";
	}
	else if (cfg.hud.theme == 2)
	{
		hud[TLC] = "╔";
		hud[TRC] = "╗";
		hud[LLC] = "╚";
		hud[LRC] = "╝";
		hud[HL] = "═";
		hud[VL] = "║";
	}
	else
	{
		hud[TLC] = " ";
		hud[TRC] = " ";
		hud[LLC] = " ";
		hud[LRC] = " ";
		hud[HL] = " ";
		hud[VL] = " ";
	}
	return hud;
}

char** snf_rascii(const char *path)
{
	checkeng(__func__);
	FILE *f = 0;
	int c = 0, i, j, x = cfg.display.resolution.width - 2, y = cfg.display.resolution.height - 2;
	char **ascii = (char**)malloc(sizeof(char*) * y);
	
	if (! ascii)
	{
		snf_werr(SNF_ERR_MEMORY, 0, __func__);
		return 0;
	}
	for (i = 0; i < y; i++)
	{
		ascii[i] = malloc(sizeof(char) * x);
		if (! ascii[i])
		{
			snf_werr(SNF_ERR_MEMORY, 0, __func__);
			free(ascii);
			return 0;
		}
	}
	if (path)
	{
		f = fopen(path, "r");
		if (! f)
			snf_werr(SNF_ERR_OPEN, path, __func__);
	}
	for (i = 0; i < y; i++)
	{
		for (j = 0; j < x; j++)
		{
			if (f)
			{
				c = fgetc(f);
				if (c >= ' ' && c < '~')
					ascii[i][j] = c;
				else
				{
					ascii[i][j] = ' ';
					if (c == '\n')
					{
						for (j++; j < x; j++)
							ascii[i][j] = ' ';
						c = 0;
					}
					else if (c == EOF)
					{
						if (fclose(f))
							snf_werr(SNF_ERR_CLOSE, path, __func__);
						f = 0;
					}
					else
						c = ' ';
				}
			}
			else
				ascii[i][j] = ' ';
		}
		if (c && f)
			fgetc(f);
	}
	if (f)
		if (fclose(f))
			snf_werr(SNF_ERR_CLOSE, path, __func__);
	return ascii;
}

char** snf_rasciirle(const char *path)
{
	FILE *in = 0, *temp = 0;
	unsigned char n;
	char i, j;
	
	in = fopen(path, "rb");
	if (! in)
	{
		snf_werr(SNF_ERR_OPEN, path, __func__);
		return 0;
	}
	temp = fopen(SNF_PATH_TMP, "w");
	if (! temp)
	{
		fclose(in);
		snf_werr(SNF_ERR_OPEN, SNF_PATH_TMP, __func__);
		return 0;
	}
	n = 0;
	i = 0;
	while (i != EOF)
	{
		if (fread(&n, sizeof(n), 1, in) != 1)
			break;
		i = fgetc(in);
		if (i == EOF)
			break;
		if (n < 127)
		{
			fwrite(&i, 1, sizeof(i), temp);
			for (j = 0; j < n; j++)
			{
				i = fgetc(in);
				if (i == EOF)
					break;
				fwrite(&i, 1, sizeof(i), temp);
			}
		}
		else
		{
			n -= 127;
			for (j = 0; j < n; j++)
				fwrite(&i, 1, sizeof(i), temp);
		}
	}
	if (fclose(in))
		snf_werr(SNF_ERR_CLOSE, path, __func__);
	if (fclose(temp))
		snf_werr(SNF_ERR_CLOSE, SNF_PATH_TMP, __func__);
	return snf_rascii(SNF_PATH_TMP);
}

void snf_prints(const char *s)
{
	checkeng(__func__);
	int resnf_setcur;

	if (! cfg.system.cursor)
	{
		snf_setcur(1);
		resnf_setcur = 1;
	}
	else resnf_setcur = 0;
	for (int c = 0; *s; s++)
	{
		putchar(*s);
		if (c != '\n')
		{
			nanosleep(&cfg.text.speed, 0);
			if (snf_kbhit())
				c = getchar();
		}
	}
	if (resnf_setcur)
		snf_setcur(0);
}

void printtitle(const char **hud, const char *name)
{
	const int len = strlen(name) + 2;
	int i;
	
	if (! hud)
	{
		printf(SNF_CLR "\n\n      %s\n\n\n" SNF_CLR_RESET, cfg.hud.color, name);
		return;
	}
	printf(SNF_CLR "\n    %s", cfg.hud.color, hud[TLC]);
	for (i = 0; i < len; i++)
		printf("%s", hud[HL]);
	printf("%s\n    %s ", hud[TRC], hud[VL]);
	printf(SNF_CLR_RESET "%s", name);
	printf(SNF_CLR " %s\n    %s", cfg.hud.color, hud[VL], hud[LLC]);
	for (i = 0; i < len; i++)
		printf("%s", hud[HL]);
	printf("%s\n\n" SNF_CLR_RESET, hud[LRC]);
}

bool printoptionsmenu()
{
	checkeng(__func__);
	CFG_SNAFU oldcfg = cfg, nesnf_wcfg = cfg;
	bool modified = 0, reload = 0;
	int c = 0, selection = 0;
	const char **hud = snf_loadhudtheme();
	
	if (! hud)
		snf_werr(SNF_ERR_RENDER, "main menu", __func__);
	while (! selection || c != '\n')
	{
		snf_clear();
		printtitle(hud, "OPTIONS");
		printf(SNF_CLR_BOLDWHITE);
		if (selection == 1)
			putchar('>');
		printf(" Resolution : ");
		if (selection != 1)
			putchar(' ');
		printf("%d x %d\n", nesnf_wcfg.display.resolution.width, nesnf_wcfg.display.resolution.height);
		if (selection == 2)
			putchar('>');
		printf(" Color :      ");
		if (selection != 2)
			putchar(' ');
		switch (nesnf_wcfg.hud.color)
		{
			case 30:
				printf("black");
				break;
			case 31:
				printf("red");
				break;
			case 32:
				printf("green");
				break;
			case 33:
				printf("yellow");
				break;
			case 34:
				printf("blue");
				break;
			case 35:
				printf("magenta");
				break;
			case 36:
				printf("cyan");
				break;
			case 37:
				printf("white");
				break;
			default:
				printf("terminal settings");
				break;
		}
		putchar('\n');
		if (selection == 3)
			putchar('>');
		printf(" Theme :      ");
		if (selection != 3)
			putchar(' ');
		switch (nesnf_wcfg.hud.theme)
		{
			case 1:
				printf("simple line");
				break;
			case 2:
				printf("double line");
				break;
			default:
				printf("empty");
				break;
		}
		putchar('\n');
		if (selection == 4)
			putchar('>');
		printf(" Text speed : ");
		if (selection != 4)
			putchar(' ');
		printf("%f\n\n", (float)nesnf_wcfg.text.speed.tv_sec + (float)nesnf_wcfg.text.speed.tv_nsec / 1000000000);
		if (modified)
		{
			if (selection == 5)
				putchar('>');
			printf(" Apply\n");
			if (selection == 6)
				putchar('>');
			printf(" Cancel\n");
		}
		if (selection == 7)
				putchar('>');
			printf(" Reset\n");
		if (selection == 8)
			putchar('>');
		printf(" Back\n" SNF_CLR_RESET);
		while (! snf_kbhit())
			snf_fsleep(0.07);
		if (snf_getarrow(&c))
		{
			if (c == SNF_KEY_UP)
			{
				selection--;
				if (! modified && (selection == 5 || selection == 6))
					selection = 4;
				else if (selection < 1)
					selection = 8;
			}
			else if (c == SNF_KEY_DOWN)
			{
				selection++;
				if (! modified && (selection == 5 || selection == 6))
					selection = 7;
				else if (selection > 8)
					selection = 1;
			}
			else if (c == SNF_KEY_RIGHT)
			{
				if (selection == 1 && nesnf_wcfg.display.resolution.width < 160)
				{
					nesnf_wcfg.display.resolution.width += 20;
					nesnf_wcfg.display.resolution.height += 6;
					modified = 1;
				}
				else if (selection == 2)
				{
					if (nesnf_wcfg.hud.color == 0)
					{
						nesnf_wcfg.hud.color = 30;
						modified = 1;
					}
					else if (nesnf_wcfg.hud.color < 37)
					{
						nesnf_wcfg.hud.color++;
						modified = 1;
					}
				}
				else if (selection == 3 && nesnf_wcfg.hud.theme < 2)
				{
					nesnf_wcfg.hud.theme++;
					modified = 1;
				}
				else if (selection == 4 && nesnf_wcfg.text.speed.tv_sec < 1)
				{
					if (nesnf_wcfg.text.speed.tv_nsec > 990000000)
					{
						nesnf_wcfg.text.speed.tv_sec = 1;
						nesnf_wcfg.text.speed.tv_nsec = 0;
						modified = 1;
					}
					else
					{
						nesnf_wcfg.text.speed.tv_nsec += 10000000;
						modified = 1;
					}
				}
			}
			else if (c == SNF_KEY_LEFT)
			{
				if (selection == 1 && nesnf_wcfg.display.resolution.width > 80)
				{
					nesnf_wcfg.display.resolution.width -= 20;
					nesnf_wcfg.display.resolution.height -= 6;
					modified = 1;
				}
				else if (selection == 2)
				{
					if (nesnf_wcfg.hud.color == 30)
					{
						nesnf_wcfg.hud.color = 0;
						modified = 1;
					}
					else if (nesnf_wcfg.hud.color > 30)
					{
						nesnf_wcfg.hud.color--;
						modified = 1;
					}
				}
				else if (selection == 3 && nesnf_wcfg.hud.theme > 0)
				{
					nesnf_wcfg.hud.theme--;
					modified = 1;
				}
				else if (selection == 4)
				{
					if (nesnf_wcfg.text.speed.tv_sec >= 1)
					{
						nesnf_wcfg.text.speed.tv_sec--;
						if (! nesnf_wcfg.text.speed.tv_sec)
							nesnf_wcfg.text.speed.tv_nsec = 990000000;
						modified = 1;
					}
					else if (nesnf_wcfg.text.speed.tv_nsec > 50000000)
					{
						nesnf_wcfg.text.speed.tv_nsec -= 10000000;
						modified = 1;
					}
				}
			}
		}
		else if (c == '\n')
		{
			if (modified && selection == 5)
			{
				cfg = nesnf_wcfg;
				hud = snf_loadhudtheme();
				if (! hud)
					snf_werr(SNF_ERR_RENDER, "options submenu", __func__);
				reload = 1;
			}
			else if (modified && selection == 6)
			{
				cfg = oldcfg;
				nesnf_wcfg = cfg;
				modified = 0;
				hud = snf_loadhudtheme();
				if (! hud)
					snf_werr(SNF_ERR_RENDER, "options submenu", __func__);
				reload = 1;
			}
			else if (selection == 7)
			{
				snf_setdefcfg();
				nesnf_wcfg = cfg;
				modified = 0;
				hud = snf_loadhudtheme();
				if (! hud)
					snf_werr(SNF_ERR_RENDER, "options submenu", __func__);
				reload = 1;
			}
			if (selection != 8)
				c = 0;
		}
	}
	free(hud);
	return reload;
}

int snf_printmainmenu()
{
	checkeng(__func__);
	int c = 0, selection = 0;
	const char **hud = snf_loadhudtheme();
	
	if (! hud)
		snf_werr(SNF_ERR_RENDER, "main menu", __func__);
	while (! selection || c != '\n')
	{
		snf_clear();
		printtitle(hud, "MAIN MENU");
		printf(SNF_CLR_BOLDWHITE);
		if (selection == 1)
			putchar('>');
		printf(" New Game\n");
		if (selection == 2)
			putchar('>');
		printf(" Load Game\n");
		if (selection == 3)
			putchar('>');
		printf(" Options\n");
		if (selection == 4)
			putchar('>');
		printf(" Quit\n" SNF_CLR_RESET);
		while (! snf_kbhit())
			snf_fsleep(0.07);
		if (snf_getarrow(&c))
		{
			if (c == SNF_KEY_UP)
			{
				selection--;
				if (selection < 1)
					selection = 4;
			}
			else if (c == SNF_KEY_DOWN)
			{
				selection++;
				if (selection > 4)
					selection = 1;
			}
		}
		else if (selection == 3 && c == '\n')
		{
			if (printoptionsmenu())
			{
				snf_wcfg();
				hud = snf_loadhudtheme();
				if (! hud)
					snf_werr(SNF_ERR_RENDER, "main menu", __func__);
			}
			c = 0;
		}
	}
	free(hud);
	return selection;
}

void snf_printhud(char **image)
{
	checkeng(__func__);
	if (cfg.display.resolution.width < 2 || cfg.display.resolution.height < 2)
		return;
	int i, j, x = cfg.display.resolution.width, y = cfg.display.resolution.height / 2;
	const char **hud = snf_loadhudtheme();
	
	if (! hud)
	{
		snf_werr(SNF_ERR_RENDER, "hud", __func__);
		snf_wdebug();
		snf_fexit();
	}
	printf(SNF_CLR "%s", cfg.hud.color, hud[TLC]);
	for (i = 0; i < x - 2; i++)
		printf("%s", hud[HL]);
	printf("%s\n" SNF_CLR_RESET, hud[TRC]);
	for (i = 0; i < y - 2; i++)
	{
		for (j = 0; j < x + 1; j++)
		{
			if (j && j < x - 1)
			{
				if (image)
					printf("%c", image[i][j - 1]);
				else
					putchar(' ');
			}
			else if (j != x)
				printf(SNF_CLR "%s" SNF_CLR_RESET, cfg.hud.color, hud[VL]);
			else
				putchar('\n');
		}
	}
	printf(SNF_CLR "%s", cfg.hud.color, hud[LLC]);
	for (i = 0; i < x - 2; i++)
		printf("%s", hud[HL]);
	printf("%s\n" SNF_CLR_RESET, hud[LRC]);
}

void snf_printsnafufx()
{
	if (cfg.display.resolution.width - 9 < 0 || cfg.display.resolution.height / 2 - 5 < 0)
		return;
	char **image = snf_rascii(0);
	int c, keep = 1, x, y;
	
	x = snf_randi(0, cfg.display.resolution.width - 7);
	y = snf_randi(0, cfg.display.resolution.height / 2 - 3);
	while (keep)
	{
		image[y][x] = 'S';
		image[y][x + 1] = 'N';
		image[y][x + 2] = 'A';
		image[y][x + 3] = 'F';
		image[y][x + 4] = 'U';
		snf_clear();
		snf_printhud(image);
		if (snf_kbhit())
		{
			c = getchar();
			if (c == 10 || c == 27 || c == ' ')
				keep = 0;
		}
		else
		{
			image[y][x] = ' ';
			image[y][x + 1] = ' ';
			image[y][x + 2] = ' ';
			image[y][x + 3] = ' ';
			image[y][x + 4] = ' ';
			x += snf_randi(-1, 1);
			if (x < 0)
				x = 0;
			else if (x > cfg.display.resolution.width - 7)
				x = cfg.display.resolution.width - 7;
			y += snf_randi(-1, 1);
			if (y < 0)
				y = 0;
			else if (y > cfg.display.resolution.height / 2 - 3)
				y = cfg.display.resolution.height / 2 - 3;
			snf_fsleep(0.2);
		}
	}
}