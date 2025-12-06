#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	compare(const void *p1, const void *p2)
{
	unsigned long long	*a = *(unsigned long long **)p1;
	unsigned long long	*b = *(unsigned long long **)p2;
	if (a[0] > b[0]) // il limite inferiore di a è maggiore di quello di b
		return (1);
	else if (a[0] < b[0]) // il limite inferiore è piú piccolo
		return (-1);
	return (0);
}

void	interval_union(unsigned long long **mat, size_t nrighe)
{
	size_t i = 0, j = 0; //r = 0;
	//unsigned long long nv;
	while (i+1 < nrighe)
	{
		//r = i;
		j = i + 1;
		// se l'intervallo successivo inizia dentro l'intervallo corrente...
		while (j < nrighe && mat[j][0] <= mat[i][1])
		{
			// ...e anche la fine dell'interfallo successivo
			// è contenuta nell'intervallo corrente, allora
			// non aggiornare nulla; altrimenti, estendi l'
			// intervallo corrente mettendo come limite sup.
			// quello dell'intervallo successivo
			if (mat[i][1] < mat[j][1])
				mat[i][1] = mat[j][1];
			mat[j][0] = 0; // flag per incrementare r
			mat[j][1] = 0;
			j++;
		}
		//if (mat[r + 1][0] == 0)
		//	r++;
		i++;
	}
//	free(mat[r + 1]);
//	mat[r + 1] = NULL;
//	r += 2;
//	while (r < nrighe)
//	{
//		free(mat[r]);
//		r++;
//	}
}

unsigned long long calc_num(unsigned long long **mat, size_t nrighe)
{
	unsigned long long res = 0;
	size_t i = 0;
	while (i < nrighe)
	{
		if(mat[i][0] != 0 && mat[i][1] != 0)
		{
			res += (mat[i][1] - mat[i][0] + 1);
			//printf("%llu\n", res);
		}
		i++;
	}
	return (res);
}

int	main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) return 1;
	char line[40];
	//char numeri[5];
	unsigned long long **mat = malloc(sizeof(unsigned long long *) * 178);
	mat[177] = NULL;
	//int v[2];
	//unsigned long long lb;
	//unsigned long long ub;
	size_t i = 0;
	while (strncmp(fgets(line, sizeof(line), fp), "\n", 1) != 0)
	{
		mat[i] = malloc(sizeof(unsigned long long) * 2);
		mat[i][0] = strtoull(line, NULL, 10);
		mat[i][1] = strtoull(strchr(line, '-') + 1, NULL, 10);
		//mat[i] = strdup(v);
		i++;
	}
	size_t nrighe = i;
	qsort(mat, nrighe, sizeof(unsigned long long *), compare);
	interval_union(mat, nrighe);
	unsigned long long res = calc_num(mat, nrighe);
	i = 0;
	//int j = 0;
	//while (i < nrighe)
	//{
	//	printf("[%llu, %llu]\n", mat[i][0], mat[i][1]);
	//	i++;
	//}
	printf("%llu\n", res);
	i = 0;
	while (i < nrighe)
	{
		free(mat[i]);
		i++;
	}
	fclose(fp);
	//while (mat[i])
	//	free(mat[i]);
	return (0);
}
