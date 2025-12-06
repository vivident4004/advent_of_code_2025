#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char line[10];
	FILE* file = fopen("input.txt", "r");
	char dir;
	int pos = 50;
	int old_pos = pos;
	int i = 0;
	int count = 0;
	int clicks = 0;
	int div = 0;
	//int fd = open("1.txt", , O_RDWR | O_CREAT);
	while (fgets(line, sizeof(line), file))
	{
		//printf("%s", line);
		dir = line[0];
		i = atoi((const char*)&line[1]);
		if (dir == 'R')
		{
		//	pos += i;
		//	old_pos = pos;
		//	pos %= 100;
		//	div = old_pos / 100;
		//	if (div > 0)
		//		clicks += div;
			while (i--)
			{
				pos++;
				pos %= 100;
				if (pos == 0)
					count++;
			}
		}
		if (dir == 'L')
		{
		//	pos -= i;
		//	old_pos = pos;
		//	pos %= 100;
		//	div = old_pos / 100;
		//	if (div < 0)
		//		clicks -= div;
			while (i--)
			{
				pos--;
				pos %= 100;
				if (pos == 0)
					count++;
			}
		}
	//	if (pos == 0)
	//		count++;

	}
	printf("%d\n", count + clicks);
	fclose(file);
	return (0);
}
