#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define HEX_BUFFER_SIZE 66
#define MAX_DISCARD_COUNT 4096

static bool is_valid_hex(const char *str, size_t max_len)
{
    size_t i = 0;
    size_t len;

    if (str == NULL || max_len == 0)
    {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len >= max_len)
    {
        return false;
    }

    if (len >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
    }

    if (len <= i)
    {
        return false;
    }

    for (; i < len; i++)
    {
        if (isxdigit((unsigned char)str[i]) == 0)
        {
            return false;
        }
    }

    return true;
}

static bool is_hex_even(const char *str, size_t max_len)
{
    size_t len;

    if (str == NULL || max_len == 0)
    {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len >= max_len)
    {
        return false;
    }

    return strchr("02468aceACE", str[len - 1]) != NULL;
}

static size_t discard_remaining_input(void)
{
    size_t discarded = 0;

    while (discarded < MAX_DISCARD_COUNT)
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n' || ch == EOF)
        {
            break;
        }

        discarded++;
    }

    return discarded;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char hex_input[HEX_BUFFER_SIZE] = {0};
    size_t input_len;

    printf("Enter a hexadecimal number: ");
    fflush(stdout);

    if (fgets(hex_input, sizeof(hex_input), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    input_len = strnlen(hex_input, sizeof(hex_input));

    if (input_len > 0 && input_len < sizeof(hex_input) && hex_input[input_len - 1] == '\n')
    {
        hex_input[input_len - 1] = '\0';
    }
    else if (input_len == sizeof(hex_input) - 1 && hex_input[input_len - 1] != '\n')
    {
        if (discard_remaining_input() > 0)
        {
            fprintf(stderr, "Error: input exceeds maximum length.\n");
            return 1;
        }
    }

    if (!is_valid_hex(hex_input, sizeof(hex_input)))
    {
        fprintf(stderr, "Error: invalid hexadecimal number.\n");
        return 1;
    }

    if (is_hex_even(hex_input, sizeof(hex_input)))
    {
        printf("%s is an even number.\n", hex_input);
    }
    else
    {
        printf("%s is an odd number.\n", hex_input);
    }

    return 0;
}