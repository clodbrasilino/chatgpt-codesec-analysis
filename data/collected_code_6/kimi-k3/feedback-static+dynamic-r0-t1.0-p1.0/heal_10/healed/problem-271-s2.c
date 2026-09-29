#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;
    char *endptr;
    long val;
    unsigned int n;
    unsigned long long result;
    size_t len;
    
    read = getline(&buffer, &buffer_size, stdin);
    
    if (read == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (read == 0)
    {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (read > 0 && buffer[read - 1] == '\n')
    {
        buffer[read - 1] = '\0';
        read--;
    }
    
    if (read > 0 && memchr(buffer, '\0', (size_t)read) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    len = strnlen(buffer, (size_t)read);
    
    if (len == 0)
    {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\0' || val < 0 || val > UINT_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    n = (unsigned int)val;
    result = sum_fifth_power_even(n);
    
    if (result == ULLONG_MAX && n > 0)
    {
        fprintf(stderr, "Overflow occurred\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", result);
    
    free(buffer);
    
    return EXIT_SUCCESS;
}