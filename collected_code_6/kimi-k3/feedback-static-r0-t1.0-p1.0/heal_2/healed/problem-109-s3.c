#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int count_odd_rotations(const char *s, size_t s_len, size_t *count)
{
    size_t i, odd_count = 0;

    if (s == NULL || count == NULL)
        return -1;

    if (s_len == 0)
    {
        *count = 0;
        return 0;
    }

    for (i = 0; i < s_len; i++)
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
    char buffer[1024];
    size_t count;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer))
    {
        fprintf(stderr, "Input too long or not null-terminated\n");
        return EXIT_FAILURE;
    }

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }

    if (count_odd_rotations(buffer, len, &count) != 0)
    {
        fprintf(stderr, "Invalid binary string\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}