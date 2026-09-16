#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nonagonal_number(long long n)
{
    unsigned long long un;

    if (n <= 0) {
        return 0;
    }

    un = (unsigned long long)n;
    return (un * ((7ULL * un) - 5ULL)) / 2ULL;
}

int main(void)
{
    long long n = 10;
    unsigned long long result = find_nonagonal_number(n);
    
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}