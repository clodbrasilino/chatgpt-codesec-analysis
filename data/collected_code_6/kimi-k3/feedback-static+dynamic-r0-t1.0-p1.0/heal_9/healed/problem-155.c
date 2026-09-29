#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 128

uint32_t toggle_even_bits(uint32_t num)
{
    return num ^ 0xAAAAAAAAU;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    uint32_t num;
    char extra;
    char *endptr;
    unsigned long val;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin))
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    val = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || val > UINT32_MAX)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    num = (uint32_t)val;

    if (sscanf(endptr, " %c", &extra) == 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_even_bits(num));

    return 0;
}