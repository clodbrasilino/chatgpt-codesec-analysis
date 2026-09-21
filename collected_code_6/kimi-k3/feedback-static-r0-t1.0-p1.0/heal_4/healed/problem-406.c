#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int find_parity(uint64_t num)
{
    return (int)(num & 1U);
}

int main(void)
{
    char input[64];
    uint64_t num;
    char *endptr;
    int parity;
    size_t len;

    printf("Enter a non-negative integer: ");

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    len = strlen(input);

    if (len == 0)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (input[len - 1] != '\n')
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    input[len - 1] = '\0';

    if (input[0] == '\0')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    num = strtoull(input, &endptr, 10);

    if (errno != 0 || *endptr != '\0' || endptr == input)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    parity = find_parity(num);

    if (parity == 0)
    {
        printf("The number is even\n");
    }
    else
    {
        printf("The number is odd\n");
    }

    return 0;
}