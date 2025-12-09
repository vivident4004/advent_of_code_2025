#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

uint64_t f(unsigned int *asc, unsigned int *ord, size_t len)
{
    size_t i = 0, j = 0;
    int max = 0;
    //int max_ord = 0;
    size_t ind[2];
    //size_t ord_ind[2];
    int temp = 0;
    uint64_t res = 0;
    while (i < len)
    {
        j = 0;
        while (j < len)
        {
            temp = asc[i] - asc[j];
            if (temp > max)
            {
                ind[0] = i;
                ind[1] = j;
                max = temp;
            }
            j++;
        }
        i++;
    }
    i = 0;
    temp = 0;
    while (i < len)
    {
        j = 0;
        while (j < len)
        {
            temp = ord[i] - ord[j];
            if (temp > max)
            {
                ind[0] = i;
                ind[1] = j;
                max = temp;
            }
            j++;
        }
        i++;
    }
    printf("punti: %lu %lu\n", ind[0], ind[1]);
    res = (asc[ind[0]] - asc[ind[1]]) * (ord[ind[0]] - ord[ind[1]]);
    return (res);
}

int  main(void)
{
    FILE *fp = fopen("prova.txt", "r");
    char line[15];
    unsigned int asc[500];
    unsigned int ord[500];
    size_t i = 0;
    char **temp;
    while (fgets(line, sizeof(line), fp))
    {
        temp = ft_split(line, ',');
        asc[i] = atoi(temp[0]);
        ord[i] = atoi(temp[1]);
        i++;
    }
    size_t j = 0;
    while (j < i)
    {
        printf("%u,%u\n", asc[j], ord[j]);
        j++;
    }
    printf("res = %lu\n", f(asc, ord, i));
    fclose(fp);
    return (0);
}
