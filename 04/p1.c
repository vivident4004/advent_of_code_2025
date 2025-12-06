#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	isroll(char obj)
{
	if (obj == '@')
		return (1);
	return 0;
}

int	fork_check(char **mat, int i, int j)
{
	int	count = 0;
	count += isroll(mat[i-1][j-1]);
	count += isroll(mat[i-1][j]);
	count += isroll(mat[i-1][j+1]);
	count += isroll(mat[i][j-1]);
	count += isroll(mat[i][j+1]);
	count += isroll(mat[i+1][j-1]);
	count += isroll(mat[i+1][j]);
	count += isroll(mat[i+1][j+1]);
	if (count >= 4)
		return (0);
	return (1);
}

// scorre la matrice e contra i rotoli di carta spostabili
unsigned long long	parse_mat(char **mat)
{
	unsigned long long count = 0;
	int i = 0, j = 0;
	while (mat[i])
	{
		j = 0;
		while (mat[i][j])
		{
			if (isroll(mat[i][j]))
				count += (unsigned long long)fork_check(mat, i, j);
			j++;
		}
		i++;
	}
	return (count);
}

int	main(void)
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) return 1;
	char line[142];
	char **mat = malloc(sizeof(char *) * 140);
	int i = 0;
	char *puntini = calloc(140, sizeof(char));
	while (i < 140)
	{
		puntini[i] = 46;
		i++;
	}
	i = 1;
	mat[0] = strdup(puntini);
	//printf("%s\n", puntini);
	char nline[139];
	int j;
	while (fgets(line, sizeof(line), fp))
	{
		nline[0] = '.';
		j = 1;
		while (j < 139)
		{
			nline[j] = line[j-1];
			j++;
		}
		nline[139] = '.';
		mat[i] = strdup(nline);
		//printf("%ld\n", strlen(line));
		//mat[i][0] = '.';
		//&mat[i][1] = strdup(line);
		//mat[i][139] = '.';
		//mat[i] = strcat(mat[i], ".");
		i++;
	}
	mat[i] = strdup(puntini);
	//j = 0;
	//while (mat[j])
	//{
	//	printf("%s\n", mat[j]);
	//	j++;
	//}
	//printf("lp = %ld, ll = %ld\n", strlen(puntini), strlen(mat[1]));
	unsigned long long res = parse_mat(mat);
	printf("%llu\n", res);
	fclose(fp);
	i = 0;
	//while (mat[i])
	//	free(mat[i]);
	return (0);
}
