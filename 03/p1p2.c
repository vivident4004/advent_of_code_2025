#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int trova_max(char *s, int end, int pos)
{
    int len = strlen(s) - pos - 2;
    //printf("len = %d\n", len);
    char max = s[len];
    int max_pos = len;
    while (len >= end)
    {
        if (s[len] >= max)
        {
            max = s[len];
            max_pos = len;
        }
        len--;
    }
    return (max_pos);
}

unsigned long long potenza(unsigned long long b, unsigned long long e)
{
    if (e == 0)
        return (1);
    unsigned long long res = 1;
    unsigned long long i = 1;
    while(i <= e)
    {
        res *= b;
        i++;
    }
    return (res);
}

unsigned long long costruisci_numero(char *s, int *posiz, int pot_max)
{
    int i = pot_max;
    int p = 12 - pot_max;
    unsigned long long num = 0;
    while (i > -1)
    {
        num += (s[posiz[p]] - '0') * potenza(10, (unsigned long long)i);
        printf("num = %llu\n", num);
        i--;
        p++;
    }
    return (num);
}
int main(int ac, char **av)
{
    int pot_max;
	if (ac == 1)
		pot_max = 1;
	else if (ac == 2)
		pot_max = atoi(av[1]);
	else
	{
		fprintf(stderr, "Inserire potenza massima: 1 per la prima parte, 11 per la seconda parte.\n");
		return (-42);
	}
    FILE *fptr = fopen("input.txt", "r");
    if (!fptr) return 1;
    char line[102];
    unsigned long long sum = 0;
    // unsigned long jolt = 0;
    // size_t max_pos = 0;
    // size_t seconda_cifra = 0;
    int *posiz = (int *)calloc(sizeof(int), 13);
    posiz[11 - pot_max] = -1;
    //posiz[10] = -1;
    //int i = 1;
    while (fgets(line, sizeof(line), fptr))
    {
        // ora ciclo per tutte le posizioni
        // nella prima posizione c'è 0, perché ho chiamato calloc,
        // in modo che possa impostare end a 0
        int i = 12 - pot_max;
        while (i < 13)
        {
            posiz[i] = trova_max(line, posiz[i - 1] + 1, 12 - i);
            printf("posiz[%i] = %i\n", i, posiz[i]);
            i++;
        }
        sum += costruisci_numero(line, posiz, pot_max);
        printf("sum per ora = %llu\n", sum);
        posiz[11 - pot_max] = -1;
        // printf("%s", line);
        // max_pos = trova_max(line, 0, 1);
        // seconda_cifra = trova_max(line, (int)(max_pos + 1), 0);
        // jolt = (line[max_pos] - 48)*10 + (line[seconda_cifra] - 48);
        // printf("%ld\n", (long)jolt);
        // sum += jolt;
    }
    printf("%llu\n", sum);
    fclose(fptr);
    return (0);
}
