#include <snafuENG.h>
#include <stdlib.h>

void	snf_image_destroy(t_img *i)
{
	free(i);
}
