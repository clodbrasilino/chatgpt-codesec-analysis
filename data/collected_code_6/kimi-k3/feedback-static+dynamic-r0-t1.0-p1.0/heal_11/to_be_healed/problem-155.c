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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

    buffer[strcspn(buffer, "\n")] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len == 0)
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