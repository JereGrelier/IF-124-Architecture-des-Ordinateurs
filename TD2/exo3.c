void main()
{
    long a, b = 2, x = 3, *p;
    p = &x;
    //...
    a = *p;
    *p = b;
    p = &b;
    //...
    (*p)++;
}