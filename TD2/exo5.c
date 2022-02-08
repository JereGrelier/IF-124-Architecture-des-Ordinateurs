void main()
{
    long t[] = {1, 2, 3, 4, 0, 0, 0, 0, 0, 0};
    long *p, *q, n = 5;
    p = t;
    q = t + n;
    do
        *(q++) = *p;
    while (*(p++) != 0);
}

void ifgoto()
{
    long t[] = {1, 2, 3, 4, 0, 0, 0, 0, 0, 0};
    long *p, *q, n = 5;
    p = t;
    q = t + n;
    debut:
    if ((*p++) == 0)
        goto fin;
    *(q++) = *p;
    goto debut;
fin:
}