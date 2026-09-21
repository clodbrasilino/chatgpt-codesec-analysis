#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

uint32_t toggle_even_bits(uint32_t num)
{
    return num ^ 0xAAAAAAAAU;
}

int main(void)
{
    char buffer[64];
    char *endptr;
    unsigned long value;
    uint32_t num;
    size_t len;
    char *p;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == 0 || len == sizeof(buffer))
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (buffer[len - 1] != '\n')
    {
        if (!feof(stdin))
        {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }
    }
    else
    {
        buffer[len - 1] = '\0';
    }

    p = buffer;
    while (isspace((unsigned char)*p))
    {
        p++;
    }

    if (*p == '\0' || *p == '-')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoul(p, &endptr, 10);

    if (errno == ERANGE || endptr == p || value > UINT32_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (isspace((unsigned char)*endptr))
    {
        endptr++;
    }

    if (*endptr != '\0')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    num = (uint32_t)value;

    printf("%" PRIu32 "\n", toggle_even_bits(num));

    return 0;
}