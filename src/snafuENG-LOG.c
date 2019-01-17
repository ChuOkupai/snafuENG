#include <snafuENG.h>

/* écrit la date et l'heure courante dans le fichier log */
void wlogtime(FILE *f)
{
	if (! f)
		return;
	time_t t = time(0);
	struct tm tm = *localtime(&t);

	fprintf(f, "%d-", tm.tm_year + 1900);
	if (tm.tm_mon + 1 < 10)
		fputc('0', f);
	fprintf(f, "%d-", tm.tm_mon + 1);
	if (tm.tm_mday < 10)
		fputc('0', f);
	fprintf(f, "%d ", tm.tm_mday);
	if (tm.tm_hour < 10)
		fputc('0', f);
	fprintf(f, "%d:", tm.tm_hour);
	if (tm.tm_min < 10)
		fputc('0', f);
	fprintf(f, "%d:", tm.tm_min);
	if (tm.tm_sec < 10)
		fputc('0', f);
	fprintf(f, "%d : ", tm.tm_sec);
}

void snf_werr(const int error, const char *data, const char *function)
{
	FILE *f = 0;

	f = fopen(SNF_PATH_LOG, "a");
	if (! f)
		return;
	wlogtime(f);
	fprintf(f, "ERROR - ");
	if (error == SNF_ERR_NODESC)
		fprintf(f, "No description.");
	else if (error == SNF_ERR_ENGINE)
		fprintf(f, "Engine not started!");
	else if (error == SNF_ERR_OPEN || error == SNF_ERR_CLOSE)
	{
		fprintf(f, "Could not ");
		fprintf(f, (error == SNF_ERR_OPEN) ? "open" : "close");	
		fprintf(f, " file %s!", data);
	}
	else if (error == SNF_ERR_MEMORY)
		fprintf(f, "Could not allocate memory!");
	else if (error == SNF_ERR_SYSTEM)
		fprintf(f, "System command returned an error!");
	else if (error == SNF_ERR_SYSTEM)
		fprintf(f, "Could not render %s!", data);
	else
		fprintf(f, "%s", data);
	fprintf(f, " (%s)\n", function);
	fclose(f);
}

void snf_wwarn(const int warning, const char *data, const char *function)
{
	FILE *f = 0;

	f = fopen(SNF_PATH_LOG, "a");
	if (! f)
		return;
	wlogtime(f);
	fprintf(f, "WARNING - ");
	if (warning == SNF_WARN_NODESC)
		fprintf(f, "No description.");
	else if (warning == SNF_WARN_CFG)
		fprintf(f, "Forbidden value set to %s!", data);
	else if (warning == SNF_WARN_EXIT)
		fprintf(f, "Exit.");
	else
		fprintf(f, "%s", data);
	fprintf(f, " (%s)\n", function);
	fclose(f);
}

void snf_wdebug()
{
	FILE *f = 0;

	f = fopen(SNF_PATH_DEBUG, "w");
	if (! f)
		return;
	fprintf(f, "%d,%d\n", cfg.display.resolution.width, cfg.display.resolution.height);
	fprintf(f, "%d,%d\n", cfg.hud.color, cfg.hud.theme);
	fprintf(f, "%d,%d\n", cfg.system.cursor, cfg.system.engine);
	fprintf(f, "%ld,%ld\n", cfg.text.speed.tv_sec, cfg.text.speed.tv_nsec);
	fclose(f);
}

int snf_rdebug()
{
	FILE *f = 0;
	CFG_SNAFU dcfg;
	int	n = 0;

	f = fopen(SNF_PATH_DEBUG, "r");
	if (! f)
		return SNF_ERR_OPEN;
	if (fscanf(f, "%d,%d", &dcfg.display.resolution.width, &dcfg.display.resolution.height))
	{
		fgetc(f);
		n += 2;
	}
	if (fscanf(f, "%d,%d", &dcfg.hud.color, &dcfg.hud.theme))
	{
		fgetc(f);
		n += 2;
	}
	if (fscanf(f, "%d,%d", &dcfg.system.cursor, &dcfg.system.engine))
	{
		fgetc(f);
		n += 2;
	}
	if (fscanf(f, "%ld,%ld", &dcfg.text.speed.tv_sec, &dcfg.text.speed.tv_nsec))
		n += 2;
	if (n == CFG_TOTAL_ELEMENTS)
	{
		puts("game.debug\n\ncfg:");
		printf("cursor=%d\nengine=%d\n", dcfg.system.cursor, dcfg.system.engine);
		printf("\ncfg.hud:\ncolor=%d\ntheme=%d\n", dcfg.hud.color, dcfg.hud.theme);
		printf("\ncfg.text:\nspeed.tv_sec=%ld\nspeed.tv_nsec=%ld\n", dcfg.text.speed.tv_sec, dcfg.text.speed.tv_nsec);
		if (fclose(f))
		return SNF_ERR_CLOSE;
	}
	return CFG_TOTAL_ELEMENTS - n;
}