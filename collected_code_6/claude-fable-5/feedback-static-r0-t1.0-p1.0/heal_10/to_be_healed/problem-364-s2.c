#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024U
#define DISCARD_GUARD_LIMIT 1000000U

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t i = 0U;

    if (str == NULL)
    {
        return 0U;
    }

    while ((i < max_len) && (str[i] != '\0'))
    {
        i++;
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

    len = bounded_length(str, max_len);

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

    len = bounded_length(str, max_len);

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

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0U;

    do
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while ((ch != '\n') && (ch != EOF) && (guard < (size_t)DISCARD_GUARD_LIMIT));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];
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

    len = bounded_length(buffer, sizeof(buffer));

    if ((len > 0U) && (buffer[len - 1U] == '\n'))
    {
        buffer[len - 1U] = '\0';
    }
    else if (len == (sizeof(buffer) - 1U))
    {
        discard_remaining_input();
        fprintf(stderr, "Input too long: maximum length is %u characters.\n",
                MAX_INPUT_SIZE - 2U);
        return EXIT_FAILURE;
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