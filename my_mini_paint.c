#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ARGS_ERR "Error: argument"
#define FILE_ERR "Error: Operation file corrupted"
char **tab, c, type;
int w, h, res;
float xs, ys, r;
FILE *fd;

void putstr(char *s) {
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

int draw(void) {
	if ((type != 'c' && type != 'C') || r <= 0)
		return -1;
	for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			if (type == 'C'){
				if (sqrtf((x - xs) * (x - xs) + (y - ys) * (y - ys)) <= r)
					tab[x][y] = c;
			}
			if (type == 'c'){
				if (sqrtf((x - xs) * (x - xs) + (y - ys) * (y - ys)) <= r
					&& r - sqrtf((x - xs) * (x - xs) + (y - ys) * (y - ys)) < 1)
					tab[x][y] = c;
			}
		}
	}
	return 0;
}

int main(int ac, char **av) {
	if (ac != 2)
		return (putstr(ARGS_ERR), 1);
	fd = fopen(av[1], "r");
	if (!fd)
		return (putstr(FILE_ERR), 1);
	res = fscanf(fd, "%d %d %c\n", &w, &h, &c);
	if (res != 3 || w <= 0 || h <= 0 || w > 300 || h > 300)
		return(putstr(FILE_ERR), 1);
	tab = calloc(h, sizeof(char *));
	for (int i = 0; i < h; i++) {
		tab[i] = calloc(w + 1, 1);
		memset(tab[i], c, w);
	}
	while ((res = fscanf(fd, "%c %f %f %f %c\n", &type, &xs, &ys, &r, &c)) != -1)
		if (res != 5 || draw() == -1)
			return (putstr(FILE_ERR), 1);
	for (int i = 0; i < h; i++)
		putstr(tab[i]);
	fclose(fd);
}
