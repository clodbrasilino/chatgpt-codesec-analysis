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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin))
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
    
    p = buffer;
    while (isspace((unsigned char)*p))
    {
        p++;
    }
    
    if (*p == '-')
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    errno = 0;
    value = strtoul(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || value > UINT32_MAX)
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