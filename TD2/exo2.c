#include <stdio.h>

int main()
{
    int u1 = 1;
    int u2 = 1;
    int i;
    int res;
    for (i = 1; i < 14; i++)
    {
        res = u2 + u1;
        u1 = u2;
        u2 = res;
    }
    printf("%d", res);
    return 0;
}