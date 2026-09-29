#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

int64_t hexagonal_number(uint32_t n, int *error)
{
    if (error == NULL)
    {
        return -1;
    }
    
    *error = 0;
    
    if (n == 0)
    {
        *error = EINVAL;
        return -1;
    }
    
    if (n > UINT32_MAX / 2)
    {
        *error = ERANGE;
        return -1;
    }
    
    uint64_t result = (uint64_t)n * (2ULL * n - 1ULL);
    
    if (result > INT64_MAX)
    {
        *error = ERANGE;
        return -1;
    }
    
    return (int64_t)result;
}

int main(void)
{
    uint32_t n;
    int error = 0;
    int64_t result;
    
    printf("Enter n: ");
    
    if (scanf("%u", &n) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    result = hexagonal_number(n, &error);
    
    if (error != 0)
    {
        fprintf(stderr, "Error calculating hexagonal number: %d\n", error);
        return 1;
    }
    
    printf("Hexagonal number: %lld\n", (long long)result);
    
    return 0;
}