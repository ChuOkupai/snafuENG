#include <snafuENG.h>
#include <unistd.h>

// TODO: -replace line 13 by an escape code to move the cursor
void	snf_image_print(const t_img *img)
{
	int y;

	y = 0;
	while (y < img->y)
	{
		write(STDOUT_FILENO, img->p[y++], img->x);
		write(STDOUT_FILENO, "\n", 1);
	}
}
