#include <snafuENG.h>

#define CFG_FILE_ELEMENTS	6
#define CFG_TOTAL_ELEMENTS	CFG_FILE_ELEMENTS + 2

typedef struct CFG_RESOLUTION
{
	int width;
	int height;
}	CFG_RESOLUTION;

typedef struct CFG_DISPLAY
{
	CFG_RESOLUTION resolution;
}	CFG_DISPLAY;

typedef struct CFG_HUD
{
	int color;
	int theme;
}	CFG_HUD;

typedef struct CFG_SYSTEM
{
	bool cursor;
	bool engine;
}	CFG_SYSTEM;

typedef struct CFG_TEXT
{
	struct timespec	speed;
}	CFG_TEXT;

typedef struct CFG_SNAFU
{
	CFG_DISPLAY	display;
	CFG_HUD		hud;
	CFG_SYSTEM	system;
	CFG_TEXT	text;
}	CFG_SNAFU;
CFG_SNAFU cfg;

void snf_wcfg()
{
	FILE *f = 0;
	
	f = fopen(SNF_PATH_CFG, "w");
	if (! f)
	{
		snf_werr(SNF_ERR_OPEN, SNF_PATH_CFG, __func__);
		return;
	}
	fprintf(f, "[DISPLAY]\n");
	fprintf(f, "resolution=%dx%d\n\n", cfg.display.resolution.width, cfg.display.resolution.height);
	fprintf(f, "[HUD]\n");
	fprintf(f, "color=%d\n", cfg.hud.color);
	fprintf(f, "theme=%d\n\n", cfg.hud.theme);
	fprintf(f, "[TEXT]\n");
	fprintf(f, "speed=%f\n", cfg.text.speed.tv_sec + (float)cfg.text.speed.tv_nsec / 1000000000);
	if (fclose(f))
		snf_werr(SNF_ERR_CLOSE, SNF_PATH_CFG, __func__);
}

void snf_rcfg()
{
	FILE *f = 0;
	char buf[18];
	float s;
	int hud = -1, display = -1, text = -1, x, y;

	f = fopen(SNF_PATH_CFG, "r");
	if (! f)
	{
		snf_werr(SNF_ERR_OPEN, SNF_PATH_CFG, __func__);
		return;
	}
	while (fgets(buf, 18, f))
	{
		if (display < 0 && strstr(buf, "[DISPLAY]"))
			display++;
		else if (hud < 0 && strstr(buf, "[HUD]"))
			hud++;
		else if (text < 0 && strstr(buf, "[TEXT]"))
			text++;
		if (hud < 0 && display < 0 && text < 0)
			continue;
		while (fgets(buf, 18, f))
		{
			if (display < 2)
			{
				if (strstr(buf, "resolution"))
				{
					sscanf(buf, "resolution=%dx%d", &x, &y);
					if ((x == 80 && y == 24)
					 || (x == 100 && y == 30)
					 || (x == 120 && y == 36)
					 || (x == 140 && y == 42)
					 || (x == 160 && y == 48))
					{
						cfg.display.resolution.width = x;
						cfg.display.resolution.height = y;
					}
					else
						snf_wwarn(SNF_WARN_CFG, "resolution", __func__);
					display += 2;
					break;
				}
			}
			if (hud < 2)
			{
				if (strstr(buf, "color"))
				{
					sscanf(buf, "color=%d", &x);
					if (! x || (x >= 30 && x <= 37))
						cfg.hud.color = x;
					else
						snf_wwarn(SNF_WARN_CFG, "HUD color", __func__);
					hud++;
					if (hud == 2)
						break;
				}
				if (strstr(buf, "theme"))
				{
					sscanf(buf, "theme=%d", &x);
					if (x >= 0 && x <= 2)
						cfg.hud.theme = x;
					else
						snf_wwarn(SNF_WARN_CFG, "HUD theme", __func__);
					hud++;
					if (hud == 2)
						break;
				}
			}
			if (text < 1)
			{
				if (strstr(buf, "speed"))
				{
					sscanf(buf, "speed=%f", &s);
					if ((int)s >= 0 && (int)s <= 1)
					{
						cfg.text.speed.tv_sec = (int)s;
						cfg.text.speed.tv_nsec = 1000000000 * (s - (int)s);
					}
					else
						snf_wwarn(SNF_WARN_CFG, "text speed", __func__);
					text += 2;	
					break;
				}
			}
		}
	}
	if (fclose(f))
		snf_werr(SNF_ERR_CLOSE, SNF_PATH_CFG, __func__);
}

void snf_setdefcfg()
{
	cfg.display.resolution.width = 80;
	cfg.display.resolution.height = 24;
	cfg.hud.color = 0;
	cfg.hud.theme = 1;
	cfg.text.speed.tv_sec = 0;
	cfg.text.speed.tv_nsec = 50000000;
}