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
 */

#ifndef SNAFUENG_H
# define SNAFUENG_H

# include <stdbool.h>
# include <time.h>

enum e_snf_key
{
	SNFKEY_ARROW_UP = 256,
	SNFKEY_ARROW_DOWN,
	SNFKEY_ARROW_RIGHT,
	SNFKEY_ARROW_LEFT,
	SNFKEY_HOME,
	SNFKEY_INS,
	SNFKEY_DEL,
	SNFKEY_END,
	SNFKEY_PAGE_UP,
	SNFKEY_PAGE_DOWN
};

typedef struct	s_snf_img
{
	char	**p;
	int		x;
	int		y;
}				t_img;

/* wait a specified number of milliseconds, break on user input */
int			snf_bdelay(clock_t ms);

/* clear the screen */
void		snf_clear(void);

/* enable or disable the cursor */
void		snf_cursor(bool show);

/* wait a specified number of milliseconds */
void		snf_delay(clock_t milliseconds);

/* print an error on STDERR_FILENO, then exit if quit is set as true */
void		snf_error(const char *function, bool quit);

/* get the next scancode from user (non blocking) */
int			snf_getc(void);

/* free the memory of a t_img */
void		snf_image_destroy(t_img *image);

/* load an image file in a t_img */
t_img*		snf_image_load(const char *path);

/* print an image on screen */
void		snf_image_print(const t_img *image);

/* check if c is an arrow key */
bool		snf_isarrow(int c);

/* check if c is a key code from snafuENG (see e_snfkey enum) */
bool		snf_iskeycode(int c);

/* check if an user input can be read */
bool		snf_kbhit(void);

/* convert a keycode in ascii (always returns a valid pointer) */
const char*	snf_ktoa(int c);

/* print a string with a delay in milliseconds between each characters */
void		snf_prints(const char *string, clock_t delay);

/* enable or disable raw mode (to prevent line buffering) */
// If raw mode is already enabled, nothing occurs.
// /!\ DISABLE before exit
void		snf_raw(bool enable);

#endif
