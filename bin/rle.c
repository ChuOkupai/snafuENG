/* 
 * rle.c - Part of snafuENG -  Data compression with RLE algorithm
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
 * 
 * How to use:
 * ./rle "SNF_PATH_0" "SNF_PATH_1" ... "SNF_PATH_n"
 * 
 * Example:
 * $> ./rle "foo"
 * It will compress the file "foo" and save it as "foo.rle"
 */
#include <stdio.h>

int rleCompress(const char *source, const char *destination)
{
	FILE 			*input = 0, *output = 0;
	unsigned char	n;
	char			neof, i, j;
	
	input = fopen(source, "r");
	if (! input)
		return 1;
	output = fopen(destination, "wb");
	if (! output)
	{
		fclose(input);
		return 2;
	}
	i = fgetc(input);
	j = fgetc(input);
	while (i != EOF)
	{
		n = 0;
		if (i == j)
		{
			while (i == j && n < 127)
			{
				j = fgetc(input);
				n++;
			}
			n += 128;
			fwrite(&n, 1, sizeof(n), output);
			fwrite(&i, 1, sizeof(i), output);
			if (j == EOF)
				break;
		}
		else
		{
			while (j != EOF && i != j && n < 127)
			{
				i = j;
				j = fgetc(input);
				n++;
			}
			neof = (j == EOF) ? 0 : 2;
			if (! neof)
				n++;
			fseek(input, -n - neof, SEEK_CUR);
			n--;
			fwrite(&n, 1, sizeof(n), output);
			n++;
			for (i = 0; i < n; i++)
			{
				j = fgetc(input);
				fwrite(&j, 1, sizeof(j), output);
			}
			if (neof)
				j = fgetc(input);
			else
				break;
		}
		i = j;
		j = fgetc(input);
	}
	fclose(input);
	fclose(output);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("%s: missing file\n", argv[0]);
		return 1;
	}
	char in[250], out[250];
	int e;
	
	for (int i = 1; i < argc; i++)
	{
		if (sprintf(in, "%s", argv[i]) < 0 || sprintf(out, "%s.rle", argv[i]) < 0)
		{
			printf("%s: %s: sprintf error\n", argv[0], argv[i]);
			return 2;
		}
		e = rleCompress(in, out);
		if (e)
		{
			printf("%s: ", argv[0]);
			if (e == 1)
				printf("%s: No such file or directory", in);
			if (e == 2)
				printf("%s: Couldn't create file", out);
			else
				printf("%s: Couldn't close file", (e == 3) ? in : out);
			putchar('\n');
			return 3;
		}
	}
	return 0;
}