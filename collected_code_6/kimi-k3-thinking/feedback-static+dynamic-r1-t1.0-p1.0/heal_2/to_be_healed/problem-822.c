#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MIN_PASSWORD_LENGTH ((size_t)8)
#define MAX_PASSWORD_LENGTH ((size_t)64)
#define INPUT_BUFFER_SIZE (MAX_PASSWORD_LENGTH + 2)

bool is_valid_password(const char *password);

static size_t bounded_strlen(const char *s, size_t max)
{
    size_t length = 0;

    if (s == NULL)
    {
        return 0;
    }

    while (length < max && s[length] != '\0')
    {
        length++;
    }

    return length;
}

bool is_valid_password(const char *password)
{
    size_t length;
    size_t i;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL)
    {
        return false;
    }

    length = bounded_strlen(password, MAX_PASSWORD_LENGTH + 1);

    if (length < MIN_PASSWORD_LENGTH || length > MAX_PASSWORD_LENGTH)
    {
        return false;
    }

    for (i = 0; i < length; i++)
    {
        unsigned char c = (unsigned char)password[i];

        if (isupper(c))
        {
            has_upper = true;
        }
        else if (islower(c))
        {
            has_lower = true;
        }
        else if (isdigit(c))
        {
            has_digit = true;
        }
        else if (ispunct(c))
        {
            has_special = true;
        }
        else
        {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[INPUT_BUFFER_SIZE];
    size_t length;
    int ch;
    bool truncated = false;

    printf("Enter password: ");

    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    length = bounded_strlen(password, sizeof(password));

    if (length > 0 && password[length - 1] == '\n')
    {
        password[length - 1] = '\0';
    }
    else if (length == sizeof(password) - 1)
    {
        truncated = true;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    if (!truncated && is_valid_password(password))
    {
        printf("Password is valid.\n");
    }
    else
    {
        printf("Password is invalid.\n");
    }

    return EXIT_SUCCESS;
}