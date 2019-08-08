#include <snafuENG.h>
#include <stdio.h>

bool	snf_isarrow(int c)
{
	return (c >= SNF_ARROW_UP && c <= SNF_ARROW_LEFT);
}
