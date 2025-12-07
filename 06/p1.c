#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "libft.h"

uint64_t	calcola_colonne(int **m, char **ops, size_t nr, size_t nc)
{
	size_t i = 0;
	size_t j = 0;
	//size_t k = 0;
	uint64_t col_res = 0;
	uint64_t res = 0;
	// scorre la matrice da sinistra a destra
	while (j < nc)
	{
		i = 0; // indice delle righe
		if (ops[j][0] == '+')
		{
			col_res = 0;
			while (i < nr - 1)
			{
				col_res += m[i][j];
				i++;
			}
		}
		else
		{
			col_res = 1;
			while (i < nr - 1)
			{
				col_res *= m[i][j];
				i++;
			}
		}
		// scorre la stringa delle operazioni
		// dopo aver calcolato ogni colonna, aggiorna il totale
		res += col_res;
		j++;
	}
	return (res);
}

int	main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) return 1;
	char line[3733];
	int **mat = calloc(5, sizeof(int *));
	char *ops;
	char **tmp;

	size_t nrighe = 4; // per il problema vero modificare a 5
	size_t ncol;
	size_t i = 0;
	size_t j = 0;
	while (fgets(line, sizeof(line), fp))
	{
		if (line[0] == '*' || line[0] == '+')
		{
			ops = line;
			break;
		}
		tmp = ft_split(line, ' ');
		j = 0;
		while (tmp[j] && tmp[j][0] != '\n')
			j++;
		//printf("count = %ld\n", j);
		mat[i] = calloc(j, sizeof(int));
		j = 0;
		while (tmp[j] && tmp[j][0] != '\n')
		{
			mat[i][j] = atoi(tmp[j]);
			//printf("%d ", mat[i][j]);
			j++;
		}
		i++;
	}
	ncol = j;
	printf("nc = %ld\n", ncol);
	char **ops_mat = ft_split(ops, ' ');
	printf("%ld\n", calcola_colonne(mat, ops_mat, nrighe, ncol));
	return (0);
}
