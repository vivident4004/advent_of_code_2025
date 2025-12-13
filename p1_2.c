#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libft.h"

#define ABS(x) (((x) < 0) ? -(x) : (x))


// struct direzione
// {
//     int su;
//     int giu;
//     int destra;
//     int sinistra;
// };

// uint64_t f(unsigned int *asc, unsigned int *ord, size_t len)
// {
//     size_t i = 0, j = 0;
//     int max = 0;
//     //int max_ord = 0;
//     size_t ind[2];
//     //size_t ord_ind[2];
//     int temp = 0;
//     uint64_t res = 0;
//     while (i < len)
//     {
//         j = 0;
//         while (j < len)
//         {
//             temp = asc[i] - asc[j];
//             if (temp > max)
//             {
//                 ind[0] = i;
//                 ind[1] = j;
//                 max = temp;
//             }
//             j++;
//         }
//         i++;
//     }
//     i = 0;
//     temp = 0;
//     while (i < len)
//     {
//         j = 0;
//         while (j < len)
//         {
//             temp = ord[i] - ord[j];
//             if (temp > max)
//             {
//                 ind[0] = i;
//                 ind[1] = j;
//                 max = temp;
//             }
//             j++;
//         }
//         i++;
//     }
//     printf("punti: %lu %lu\n", ind[0], ind[1]);
//     res = (asc[ind[0]] - asc[ind[1]]) * (ord[ind[0]] - ord[ind[1]]);
//     return (res);
// }

uint64_t calcola_aree(int *asc, int *ord, size_t len)
{
    size_t i = 0, j = 0;
    uint64_t area = 0, max_area = 0;
    while (i < len)
    {
        j = 0;
        while (j < len)
        {
            if (asc[j])
            area = (uint64_t)(ABS(asc[i] - asc[j]) + 1) * (uint64_t)(ABS(ord[i] - ord[j]) + 1);
            if (area > max_area)
                max_area = area;
            j++;
        }
        i++;
    }
    return max_area;
}

// uint64_t calcola_aree_mod(int *asc, int *ord, int **pos, size_t len)
// {
//     size_t i = 0, j = 0;
//     uint64_t area = 0, max_area = 0;
//     while (i < len)
//     {
//         j = 0;
//         while (j < len)
//         {
//             area = (uint64_t)(ABS(asc[i] - asc[j]) + 1) * (uint64_t)(ABS(ord[i] - ord[j]) + 1);
//             if (area > max_area)
//                 max_area = area;
//             j++;
//         }
//         i++;
//     }
//     return max_area;
// }

void riempi_verde(char **mat, int i, int j, int passi, size_t direzione)
{
    // int k = 0;
    if (direzione == 0) // verso l'alto 
    {
        while (passi)
        {
            i--;
            mat[i][j] = 'X';
            passi--;
        }
    }
    else if (direzione == 1) // verso il basso
    {
        while (passi)
        {
            i++;
            mat[i][j] = 'X';
            passi--;
        }
    }
    else if (direzione == 2) // verso sinistra
    {
        while (passi)
        {
            j--;
            mat[i][j] = 'X';
            passi--;
        }
    }
    else if (direzione == 3) // verso destra
    {
        while (passi)
        {
            j++;
            mat[i][j] = 'X';
            passi--;
        }
    }
}

void crea_mat(char **mat, int *asc, int *ord, size_t len, int a_max, int o_max)
{
    int lunghezze[4];
    size_t i = 0;
    int x = 0, y = 0;
    while(i < len)
    {
        y = asc[i];
        x = ord[i];
        mat[x][y] = '#';
        i++;
    }
    return ;
    i = 0;
    // size_t j = 0;
    int k = 0;
    while (i < len)
    {
        y = asc[i];
        x = ord[i];
        k = 0;
        while ((x + k) > 0 && mat[x + k][y] != '#')
            k--;
        lunghezze[0] = ABS(k+1); // indice verso l'alto
        k = 0;
        while ((x + k) < o_max && mat[x + k][y] != '#')
            k++;
        lunghezze[1] = ABS(k-1); // indice verso il basso
        k = 0;
        while ((y + k) > 0 && mat[x][y + k] != '#')
            k--;
        lunghezze[2] = ABS(k+1); // indice verso sinistra
        k = 0;
        while ((y + k) < a_max && mat[x][y + k] != '#')
            k++;
        lunghezze[3] = ABS(k-1); // indice verso destra
        int min = lunghezze[0];
        size_t min_idx = 0;
        k = 1;
        while (k < 4)
        {
            if (lunghezze[k] < min)
            {
                min = lunghezze[k];
                min_idx = k;
            }
            k++;
        }
        riempi_verde(mat, x, y, min, min_idx);
        i++;
    }
}

int  main(void)
{
    FILE *fp = fopen("prova.txt", "r");
    char line[15];
    int asc[500];
    int ord[500];
    // int pos[500][2];
    size_t i = 0;
    int r = 15418, l = 0;
    char **temp;
    while (fgets(line, sizeof(line), fp))
    {
        temp = ft_split(line, ',');
        asc[i] = atoi(temp[0]);
        ord[i] = atoi(temp[1]);
        if (asc[i] < l)
            l = asc[i];
        if (asc[i] > r)
            r = asc[i];
        i++;
    }
    size_t j = 0;
    // while (j < i)
    // {
    //     //printf("%u,%u\n", asc[j], ord[j]);
    //     // TODO mettere un controllo anche sul lato destro,
    //     // e il contrllo deve prendere anche pos[j-1] per
    //     // capire se il muro limite continua o no
    //     pos[j][0] = l, pos[j][1] = r;
    //     if (asc[j] > l)
    //         pos[j][0] = asc[j];
    //     j++;
    //     printf("[%d,%d]", pos[j])
    // }
    int a_max = 0;
    while (j < i)
    {  
        if (asc[j] > a_max)
            a_max = asc[j];
        j++;    
    }
    j = 0;
    int o_max = 0;
    while (j < i)
    {  
        if (ord[j] > o_max)
            o_max = ord[j];
        j++;    
    }
    char **mat = calloc(o_max + 1, sizeof(char *));
    // write(1, "test", 4);
    // printf("NUMERO RIGHE DIO MADONNA: %d", a_max);
    j = 0;
    while (j < o_max)
    {
        mat[j] = calloc(a_max + 1, sizeof(char));
        j++;
    }
    // write(1, "test", 4);
    // printf("NUMERO COLONNE DIO MADONNA: %d", o_max);
    crea_mat(mat, asc, ord, i, a_max, o_max);
    // printf("res = %lu\n", f(asc, ord, i));
    // printf("res = %lu\n", calcola_aree(asc, ord, i));
    int a = 0, b = 0;
    while (a < o_max)
    {
        b = 0;
        while (b < a_max)
        {
            printf("%c", mat[a][b]);
            b++;
        }
        printf("\n");
        a++;
    }
    fclose(fp);
    return (0);
}
