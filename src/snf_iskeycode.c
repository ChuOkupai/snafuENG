#include <snafuENG.h>
#include <stdio.h>

bool	snf_iskeycode(int c)
{
	return (c >= SNFKEY_ARROW_UP && c <= SNFKEY_PAGE_DOWN);
}
