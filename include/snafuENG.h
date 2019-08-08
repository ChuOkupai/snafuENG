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

enum e_snfkey
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

/* wait a specified number of milliseconds, break on user input */
int		snf_bdelay(clock_t ms);

/* clear the screen */
void	snf_clear(void);

/* enable or disable the cursor */
void	snf_cursor(bool show);

/* wait a specified number of milliseconds */
void	snf_delay(clock_t milliseconds);

/* print an error on STDERR_FILENO, then exit if quit is set as true */
void	snf_error(const char *function, bool quit);

/* get the next scancode from user (non blocking) */
int		snf_getc(void);

/* initialize snafuENG */
void	snf_init(void);

/* check if c is an arrow key */
bool	snf_isarrow(int c);

/* check if c is a key code from snafuENG (see e_snfkey enum) */
bool	snf_iskeycode(int c);

/* convert a keycode in ascii (always returns a valid pointer) */
char*	snf_ktoa(int c);

/* print a string with a delay in milliseconds between each characters */
void	snf_prints(const char *string, clock_t delay);

#endif
