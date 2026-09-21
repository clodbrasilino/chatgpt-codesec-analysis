#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

unsigned long long sum_fifth_power_even(unsigned int n)
{
    unsigned long long sum = 0;
    unsigned long long i;
    
    for (i = 1; i <= n; i++)
    {
        unsigned long long even_num = 2 * i;
        unsigned long long power = even_num * even_num * even_num * even_num * even_num;
        
        if (sum > ULLONG_MAX - power)
        {
            return ULLONG_MAX;
        }
        
        sum += power;
    }
    
    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    unsigned int n;
    unsigned long long result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer))
    {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || val < 0 || val > UINT_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0')
    {
        if (!isspace((unsigned char)*endptr))
        {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    n = (unsigned int)val;
    result = sum_fifth_power_even(n);
    
    if (result == ULLONG_MAX && n > 0)
    {
        fprintf(stderr, "Overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    return EXIT_SUCCESS;
}