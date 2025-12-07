#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//#include "libft.h"

uint64_t	calcola_colonne(char **mat, size_t nr, size_t nc)
{
	size_t i = nr - 1;
	int j = nc - 1;
	//size_t k = 0;
	uint64_t col_res = 0;
	uint64_t res = 0;
	// scorre la matrice da sinistra a destra
	char num[5];
	char op;
	int old_j;
	while (j >= 0)
	{
		// trova l'op
		old_j = j;
		while (mat[nr-1][j] == ' ')
			j--;
		op = mat[nr-1][j];
		if (op == '+')
		{
			col_res = 0;
			while (old_j >= j)
			{
				i = 0;
				while (i < nr - 1)
				{
					num[i] = mat[i][old_j];
					i++;
				}
				// ho finito di estrarre il numero -> lo aggiungo al risultato
				col_res += atoi(num);
				//printf("%d\n", atoi(num));
				old_j--;
			}
		}
		else
		{
			col_res = 1;
			while (old_j >= j)
			{
				i = 0;
				while (i < nr - 1)
				{
					num[i] = mat[i][old_j];
					i++;
				}
				// ho finito di estrarre il numero -> lo aggiungo al risultato
				col_res *= atoi(num);
				//printf("%d\n", atoi(num));
				old_j--;
			}
		}
		// passo ai numeri successivi, e diminuisco j che puntava ancora
		// all'operazione precedente
		j -= 2;
		res += col_res;
	}
	return (res);
}

int	main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) return 1;
	char line[3734];
	size_t nc = 0;
	size_t nr = 5;
	char **mat = calloc(nr, sizeof(char *));

	size_t i = 0;
	//size_t j = 0;

	while (fgets(line, sizeof(line), fp))
	{
		mat[i] = strdup(line);
		//printf("%s, strelen = %ld", mat[0], strlen(line));
		i++;
	}
	nc = strlen(mat[0]);
	//char *num = "    ";
	//printf("atoi: |%d|\n", atoi(num));
	// non ho capito perché al numero di colonne vada passato nc + 1, ma funziona
	printf("nc = %ld; res = %ld\n", nc, calcola_colonne(mat, nr, nc + 1));

	return (0);
}

