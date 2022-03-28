/**
 * @file exo2.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// C Version
int modulo(int n, int k) {
    while (n >= k)
    {
        n-=k;
    }
    return n;
}

// -----------------------------------------------

//Goto Version
void v2(int n, int k)
{
    debutModulo:
        if(n-k < 0)
            goto finModulo;
        n=n-k;
        goto debutModulo;
    finModulo:
        return n;
}

// ------------------------------------------------

//Syntaxic Assembly version
void v2(int n, int k)
{
    int eax = n;
    int ecx = k;
    debutModulo:
        if(eax - ecx < 0)
            goto finModulo;
        eax=eax-ecx;
        goto debutModulo;
    finModulo:
        return eax;
}