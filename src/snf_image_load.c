#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <snafuENG.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE		1024
#define SNFIMG_X_LIMIT	1024
#define SNFIMG_Y_LIMIT	512

// TODO: use stdio.h to load file + optimization
//       check memory leaks

static char	*snf_bufcpy(char *dest, const char *src, int n)
{
	char *d;

	d = dest;
	while (n--)
		*d++ = *src++;
	return (dest);
}

static char	*snf_file_load(const char *path)
{
	char	*content;
	char	*tmp;
	char	buf[BUFFER_SIZE];
	int		f;
	int		len;
	int		size;

	if ((f = open(path, O_RDONLY)) < 0)
		snf_error(__func__, true);
	if (!(content = (char*)malloc(sizeof(char))))
		snf_error(__func__, true);
	*content = '\0';
	size = 0;
	while ((len = read(f, buf, BUFFER_SIZE)) > 0)
	{
		if (!(tmp = (char*)malloc((size + len + 1) * sizeof(char))))
			break ;
		tmp = snf_bufcpy(tmp, content, size);
		free(content);
		snf_bufcpy(tmp + size, buf, len);
		content = tmp;
		size += len;
		content[size] = '\0';
	}
	close(f);
	if (len)
		snf_error(__func__, true);
	return (content);
}

static int	snf_linelen(const char *buf)
{
	int i;

	i = 0;
	while (buf[i])
		if (buf[i++] == '\n')
			break ;
	return (i);
}

t_img*		snf_image_load(const char *path)
{
	char	*buf;
	char	*s;
	int		i;
	int		len;
	t_img	*img;


	buf = snf_file_load(path);
	if (!(img = (t_img*)malloc(sizeof(t_img))))
		snf_error(__func__, true);
	s = buf;
	len = snf_linelen(s);
	if (!sscanf(s, "%dx%d", &img->x, &img->y))
		snf_error(__func__, true);
	if (img->x < 1 || img->x > SNFIMG_X_LIMIT
		|| img->y < 1 || img->y > SNFIMG_Y_LIMIT)
	{
		errno = EINVAL;
		snf_error(__func__, true);
	}
	if (!(img->p = (char**)malloc(img->y * sizeof(char*))))
		snf_error(__func__, true);
	i = 0;
	s += len;
	while (i < img->y && (len = snf_linelen(s)) > 0)
	{
		if (len < img->x)
		{
			errno = EINVAL;
			snf_error(__func__, true);
		}
		if (!(img->p[i++] = strndup(s, img->x)))
			snf_error(__func__, true);
		s += len;
	}
	free(buf);
	return (img);
}
