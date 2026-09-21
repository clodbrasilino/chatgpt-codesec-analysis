#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int find_parity(uint64_t num)
{
    return (int)(num & 1U);
}

int main(void)
{
    uint64_t num;
    int parity;
    char buffer[256];
    char *endptr;
    unsigned long long value;

    printf("Enter a non-negative integer: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (buffer[0] == '\n' || buffer[0] == '\0')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (value > UINT64_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    num = (uint64_t)value;
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