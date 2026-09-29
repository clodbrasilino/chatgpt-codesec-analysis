#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int count_odd_rotations(const char *s, size_t *count)
{
    size_t len, i, odd_count = 0;

    if (s == NULL || count == NULL)
        return -1;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s);
    if (len == 0)
    {
        *count = 0;
        return 0;
    }

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';

    if (count_odd_rotations(buffer, &count) != 0)
    {
        fprintf(stderr, "Invalid binary string\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}