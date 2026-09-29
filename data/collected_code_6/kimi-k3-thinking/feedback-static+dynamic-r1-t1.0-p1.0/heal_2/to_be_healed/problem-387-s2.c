#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 66

int isEvenHex(unsigned long long number)
{
    return (number & 1ULL) == 0ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *endptr;
    unsigned long long number;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    printf("Enter a hexadecimal number: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin))
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        fprintf(stderr, "Input exceeds maximum allowed length.\n");
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