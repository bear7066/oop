#include <stdio.h>
int main()
{
	char c;
	int xsum = 0, ysum = 0;
    scanf("%d %d", &xsum, &ysum);
   
	while (scanf("%c", &c) != EOF)
	{
		//int coordinates;
		int number;
		
		if(number != 0)
		{
			continue;
		if (c == 'T')
		{
			int t = 0, j = 0;
			scanf("%d %d", &t, &j);
			xsum = t;
			ysum = j;
		}

		scanf("%d", &number);
		
		

		if (c == 'U')
		{
			ysum += number;
		}
		else if (c == 'D')
		{
			ysum -= number;
		}
		else if (c == 'L')
		{
			xsum -= number;
		}
		else if (c == 'R')
		{
			xsum += number;
		}
		else if (c == 'S')
		{
			number--;
			continue;			
		}
	}	
}
	printf("(%d, %d)\n", xsum, ysum);
	return 0;
}
