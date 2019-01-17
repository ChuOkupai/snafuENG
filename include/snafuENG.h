/* 
 * snafuENG.h - Open source game engine for making RPG on Linux terminal
 * Copyright (C) 2019  Adrien Soursou
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Contact: adrien.soursou@ens.uvsq.fr
 * Repo:    https://github.com/ChuOkupai/snafuENG
 * Version: 0.1-00
 */

#ifndef _SNAFUENG_H
# define _SNAFUENG_H

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#define SNF_PATH_CFG	"data/game.cfg"
#define SNF_PATH_DEBUG	"game.debug"
#define SNF_PATH_LOG	"game.log"
#define SNF_PATH_IMG	"data/images/"
#define SNF_PATH_TMP	"data/.tmpfile"

typedef int bool;
#define false	0
#define true	1

#define SNF_CLR				"\033[%dm"
#define SNF_CLR_RESET		"\033[0m"
#define SNF_CLR_BLACK		"\033[30m"
#define SNF_CLR_RED			"\033[31m"
#define SNF_CLR_GREEN		"\033[32m"
#define SNF_CLR_YELLOW		"\033[33m"
#define SNF_CLR_BLUE		"\033[34m"
#define SNF_CLR_MAGENTA		"\033[35m"
#define SNF_CLR_CYAN		"\033[36m"
#define SNF_CLR_WHITE		"\033[37m"
#define SNF_CLR_BOLDBLACK	"\033[1m\033[30m"
#define SNF_CLR_BOLDRED		"\033[1m\033[31m"
#define SNF_CLR_BOLDGREEN	"\033[1m\033[32m"
#define SNF_CLR_BOLDYELLOW	"\033[1m\033[33m"
#define SNF_CLR_BOLDBLUE	"\033[1m\033[34m"
#define SNF_CLR_BOLDMAGENTA	"\033[1m\033[35m"
#define SNF_CLR_BOLDCYAN	"\033[1m\033[36m"
#define SNF_CLR_BOLDWHITE	"\033[1m\033[37m"

/* écriture d'un message d'erreur dans le fichier log */
#define SNF_ERR_NODESC	100
#define SNF_ERR_ENGINE	101
#define SNF_ERR_OPEN	102
#define SNF_ERR_CLOSE	103
#define SNF_ERR_MEMORY	104
#define SNF_ERR_SYSTEM	105
#define SNF_ERR_RENDER	106
void snf_werr(const int error, const char *data, const char *function);

/* écriture d'un message d'avertissement dans le fichier log */
#define SNF_WARN_NODESC	200
#define SNF_WARN_CFG	201
#define SNF_WARN_EXIT	202
void snf_wwarn(const int warning, const char *data, const char *function);

/* écriture des valeurs des variables globales en mémoire sur le fichier de débogage */
void snf_wdebug();

/* lecture du fichier de débogage */
int snf_rdebug();

/* forcer la fermeture du programme */
void snf_fexit();

/* attendre un nombre de secondes s */
void snf_fsleep(const float s);

/* renvoyer un int aléatoire entre min et max */
int snf_randi(const int min, const int max);

/* détecter si une touche du clavier a été frappée */
/** renvoie une valeur non nulle si vrai **/
int snf_kbhit();

/* attendre que l'utilisateur presse la touche entrée */
/** équivalent de getchar() **/
int snf_waitret();

/* récupérer l'appuie d'une touche fléchée */
#define SNF_KEY_UP		65
#define SNF_KEY_DOWN	66
#define SNF_KEY_RIGHT	67
#define SNF_KEY_LEFT	68
/** renvoie une valeur non nulle si vrai **/
bool snf_getarrow(int *c);

/* activer ou désactiver le curseur */
void snf_setcur(const bool on);

/* écriture du fichier de configuration */
void snf_wcfg();

/* lecture du fichier de configuration */
void snf_rcfg();

/* utiliser la configuration par défaut */
void snf_setdefcfg();

/* initialiser snafu */
void snf_seteng(const bool on);

/* lecture et chargement en mémoire d'une image ascii */
char** snf_rascii(const char *path);

/* lecture et chargement en mémoire d'une image ascii compressée */
char** snf_rasciirle(const char *path);

/* nettoyage de l'écran */
void snf_clear();

/* afficher une chaîne de caractères avec un délai entre chaque caractère */
/** le joueur peut passer l'animation en appuyant sur la touche entrée **/
void snf_prints(const char *s);

/* afficher le menu principal et attendre une sélection du joueur */
int snf_printmainmenu();

/* afficher l'interface avec une image ascii */
/** si l'image est nulle, affiche uniquement le hud **/
void snf_printhud(char **image);

/* affiche SNAFU animé avec un déplacement aléatoire */
/** pour arrêter l'animation, appuyez sur échap, entrée ou espace **/
void snf_printsnafufx();

#endif /* snafuENG.h */