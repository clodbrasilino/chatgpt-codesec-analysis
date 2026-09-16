#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define HEX_BUFFER_SIZE 66

static bool is_valid_hex(const char *str)
{
    size_t i = 0;
    size_t len;

    if (str == NULL || str[0] == '\0')
    {
        return false;
    }

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
    }

    len = strlen(str);
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

static bool is_hex_even(const char *str)
{
    char last = str[strlen(str) - 1];

    return strchr("02468aceACE", last) != NULL;
}

int main(void)
{
    char hex_input[HEX_BUFFER_SIZE];

    printf("Enter a hexadecimal number: ");

    if (fgets(hex_input, sizeof(hex_input), stdin) == NULL)
    {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    if (strchr(hex_input, '\n') == NULL && !feof(stdin))
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        fprintf(stderr, "Error: input exceeds maximum length.\n");
        return 1;
    }

    hex_input[strcspn(hex_input, "\n")] = '\0';

    if (!is_valid_hex(hex_input))
    {
        fprintf(stderr, "Error: invalid hexadecimal number.\n");
        return 1;
    }

    if (is_hex_even(hex_input))
    {
        printf("%s is an even number.\n", hex_input);
    }
    else
    {
        printf("%s is an odd number.\n", hex_input);
    }

    return 0;
}