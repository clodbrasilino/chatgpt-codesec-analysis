#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

int isEvenHex(unsigned long long number)
{
    return (number & 1ULL) == 0ULL;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t input_length = 0;
    char *endptr = NULL;
    unsigned long long number = 0ULL;

    printf("Enter a hexadecimal number: ");
    fflush(stdout);

    input_length = getline(&buffer, &buffer_size, stdin);

    if (input_length < 0)
    {
        fprintf(stderr, "Failed to read input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(buffer, &endptr, 16);

    if (endptr == buffer)
    {
        fprintf(stderr, "No hexadecimal digits were provided.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (errno == ERANGE)
    {
        fprintf(stderr, "Hexadecimal number is out of range.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (*endptr != '\n' && *endptr != '\0')
    {
        fprintf(stderr, "Invalid character in input.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (isEvenHex(number))
    {
        printf("%llX is even.\n", number);
    }
    else
    {
        printf("%llX is odd.\n", number);
    }

    free(buffer);
    return EXIT_SUCCESS;
}