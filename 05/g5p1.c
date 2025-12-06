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

int	main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) return 1;
	char line[40];
	//char numeri[5];
	unsigned long long **mat = malloc(sizeof(unsigned long long *) * 200);
	//mat[177] = NULL;
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
	//i = 0;
	//int j = 0;
	//while (i < nrighe)
	//{
	//	printf("[%llu, %llu]\n", mat[i][0], mat[i][1]);
	//	i++;
	//}
	
	// TODO scrivere il parsing dei numeri dopo gl'intervalli, e la ricerca dei numeri negl'intervalli creati prima.
	unsigned long long num = 0;
	int count = 0;
	while (fgets(line, sizeof(line), fp))
	{
		num = strtoull(line, NULL, 10);
		i = 0;
		while (i < nrighe && mat[i][0] <= num)
		{
			if (mat[i][1] >= num)
			{
				count++;
				break;
			}
			i++;
		}
	}
	printf("%d\n", count);
	fclose(fp);
	//while (mat[i])
	//	free(mat[i]);
	return (0);
}
