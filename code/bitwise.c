#include <stdio.h>
int addWise(int x, int y)
{
    if (y == 0)
        return x;
    else
        return addWise( x ^ y, (x & y) << 1);
}

int subWise(int x, int y)
{
    if (y == 0)
        return x;
    else
        return subWise( x ^ y, (~x & y) << 1);
}

int multWise(int x, int y)
{
	if (y == 1)
        return x;
	else
		return addWise(x, multWise(x, subWise(y, 1)));
}

int divWise(int x, int y)
{
	if (x < y)
        return 0;
	else
		return addWise(1, divWise(subWise(x, y), y));
}


//int main()
//{
//	int a = 69;
//	int b = 5;
//	printf("%d", Add(Div(a, b), Sub(a, b)));
//}
