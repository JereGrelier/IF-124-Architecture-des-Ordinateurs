void main()
{
    long t[4] = {1, 2, 3, 4};
    long n = 4;
    for (int i = 0; i < n - 1; i++)
        t[i] = t[i + 1];
}

void secver()
{
    int i = 0;
    long t[4] = {1, 2, 3, 4};
    long n = 4;
    while (i < n - 1)
    {
        t[i] = t[i + 1];
        i++;
    }
}

void ifgoto()
{
    int i = 0;
    long t[4] = {1, 2, 3, 4};
    long n = 4;
debut:
    if (n - 1 - i >= 0)
        goto fin;
    t[i] = t[i + 1];
    i++;
    goto debut;

fin:
}