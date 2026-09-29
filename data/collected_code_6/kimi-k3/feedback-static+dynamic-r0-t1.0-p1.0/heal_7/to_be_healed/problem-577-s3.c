#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int get_last_factorial_digit(int n, int *result)
{
    if (result == NULL)
    {
        return -1;
    }
    
    if (n < 0)
    {
        return -1;
    }
    
    if (n >= 5)
    {
        *result = 0;
        return 0;
    }
    
    switch (n)
    {
        case 0:
        case 1:
            *result = 1;
            break;
        case 2:
            *result = 2;
            break;
        case 3:
            *result = 6;
            break;
        case 4:
            *result = 4;
            break;
        default:
            return -1;
    }
    
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    long input_value;
    int result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    else if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n')
    {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    input_value = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || input_value > INT_MAX || input_value < INT_MIN)
    {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || *endptr != '\0')
    {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }
    
    if (get_last_factorial_digit((int)input_value, &result) != 0)
    {
        fprintf(stderr, "Invalid input: number must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}