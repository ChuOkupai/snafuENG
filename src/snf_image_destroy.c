#include <snafuENG.h>
#include <stdlib.h>

void	snf_image_destroy(t_img *img)
{
	while (img->y--)
		free(img->p[img->y]);
	free(img->p);
	free(img);
}
