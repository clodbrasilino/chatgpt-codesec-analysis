#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

static int count_odd_rotations(const char *s, size_t s_size, size_t *count)
{
    size_t len, i, odd_count = 0;

    if (s == NULL || count == NULL || s_size == 0)
        return -1;

    len = strnlen(s, s_size);
    if (len == 0)
    {
        *count = 0;
        return 0;
    }

    if (len == s_size)
        return -1;

    for (i = 0; i < len; i++)
    {
        if (s[i] != '0' && s[i] != '1')
            return -1;
        if (s[i] == '1')
            odd_count++;
    }

    *count = odd_count;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    size_t count;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    if (count_odd_rotations(buffer, sizeof(buffer), &count) != 0)
    {
        fprintf(stderr, "Invalid binary string\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}