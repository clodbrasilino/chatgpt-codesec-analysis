#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int isEvenHex(unsigned long long number)
{
    return (number & 1ULL) == 0ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[66];
    char *endptr;
    unsigned long long number;

    printf("Enter a hexadecimal number: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(buffer, &endptr, 16);

    if (endptr == buffer)
    {
        fprintf(stderr, "No hexadecimal digits were provided.\n");
        return EXIT_FAILURE;
    }

    if (errno == ERANGE)
    {
        fprintf(stderr, "Hexadecimal number is out of range.\n");
        return EXIT_FAILURE;
    }

    if (*endptr != '\n' && *endptr != '\0')
    {
        fprintf(stderr, "Invalid character in input.\n");
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

    return EXIT_SUCCESS;
}