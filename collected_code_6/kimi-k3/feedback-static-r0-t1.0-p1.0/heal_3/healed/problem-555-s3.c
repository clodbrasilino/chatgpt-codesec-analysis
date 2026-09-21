#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long calculate_difference(int n)
{
    long long sum_n = (long long)n * (n + 1) / 2;
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    char *endptr;
    long input;
    int n;
    long long result;

    bytes_read = getline(&buffer, &buffer_size, stdin);
    if (bytes_read == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input format\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (input < 1 || input > INT_MAX)
    {
        fprintf(stderr, "Input out of valid range\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    n = (int)input;
    result = calculate_difference(n);
    printf("%lld\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}