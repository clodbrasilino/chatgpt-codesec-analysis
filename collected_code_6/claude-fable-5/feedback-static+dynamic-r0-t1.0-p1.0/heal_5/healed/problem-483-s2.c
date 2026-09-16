#include <stdio.h>
#include <stdlib.h>

static unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long m)
{
    return (unsigned long long)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)m);
}

unsigned long long first_factorial_divisible(unsigned long long x)
{
    unsigned long long remainder;
    unsigned long long i;

    if (x == 1ULL) {