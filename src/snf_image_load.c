#include <snafuENG.h>
#include <stdlib.h>

// TODO: use unistd.h with system calls to load the file
t_img*	snf_image_load(const char *path)
{
	t_img *i;

	if (!(i = (t_img*)malloc(sizeof(t_img))))
		snf_error(__func__, true);
	(void)path;
	return (NULL);
}
