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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    char *endptr;
    long input_value;
    int result;
    
    bytes_read = getline(&buffer, &buffer_size, stdin);
    
    if (bytes_read == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
    {
        buffer[bytes_read - 1] = '\0';
    }
    
    errno = 0;
    input_value = strtol(buffer, &endptr, 10);
    
    if (errno == ERANGE || input_value > INT_MAX || input_value < INT_MIN)
    {
        fprintf(stderr, "Input out of range\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer || *endptr != '\0')
    {
        fprintf(stderr, "Invalid input format\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (get_last_factorial_digit((int)input_value, &result) != 0)
    {
        fprintf(stderr, "Invalid input: number must be non-negative\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    
    free(buffer);
    return EXIT_SUCCESS;
}