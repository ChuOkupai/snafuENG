#include <snafuENG.h>
#include <stdio.h>

bool	snf_isarrow(int c)
{
	return (c >= SNFKEY_ARROW_UP && c <= SNFKEY_ARROW_LEFT);
}
