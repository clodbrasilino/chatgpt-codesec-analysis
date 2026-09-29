#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1024U

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL)
    {
        return 0U;
    }

    for (i = 0U; i < max_len; i++)
    {
        if (str[i] == '\0')
        {
            break;
        }
    }

    return i;
}

static int is_binary_string(const char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL)
    {
        return 0;
    }

    len = bounded_strlen(str, max_len);

    if (len == 0U)
    {
        return 0;
    }

    if (len >= max_len)
    {
        return 0;
    }

    for (i = 0U; i < len; i++)
    {
        if ((str[i] != '0') && (str[i] != '1'))
        {
            return 0;
        }
    }

    return 1;
}

static long min_flips_to_alternate(const char *str, size_t max_len)
{
    long flips_start_zero = 0L;
    long flips_start_one = 0L;
    size_t i;
    size_t len;
    char expected_zero;
    char expected_one;

    if (str == NULL)
    {
        return -1L;
    }

    len = bounded_strlen(str, max_len);

    if (len >= max_len)
    {
        return -1L;
    }

    for (i = 0U; i < len; i++)
    {
        if ((i % 2U) == 0U)
        {
            expected_zero = '0';
            expected_one = '1';
        }
        else
        {
            expected_zero = '1';
            expected_one = '0';
        }

        if (str[i] != expected_zero)
        {
            flips_start_zero++;
        }

        if (str[i] != expected_one)
        {
            flips_start_one++;
        }
    }

    return (flips_start_zero < flips_start_one) ? flips_start_zero : flips_start_one;
}

int main(void)
{
    char buffer[MAX_INPUT_LENGTH];
    long result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a binary string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = bounded_strlen(buffer, sizeof(buffer));

    if ((len > 0U) && (buffer[len - 1U] == '\n'))
    {
        buffer[len - 1U] = '\0';
    }

    if (is_binary_string(buffer, sizeof(buffer)) == 0)
    {
        fprintf(stderr, "Invalid input: string must be non-empty and contain only '0' and '1'.\n");
        return EXIT_FAILURE;
    }

    result = min_flips_to_alternate(buffer, sizeof(buffer));

    if (result < 0L)
    {
        fprintf(stderr, "Error computing flips.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of flips required: %ld\n", result);

    return EXIT_SUCCESS;
}