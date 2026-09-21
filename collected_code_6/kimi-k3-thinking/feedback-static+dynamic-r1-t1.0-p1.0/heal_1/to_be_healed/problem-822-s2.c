#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PASSWORD_MIN_LENGTH 8U
#define PASSWORD_MAX_LENGTH 64U
#define INPUT_BUFFER_SIZE   128

static bool is_special_character(char c)
{
    const char *specials = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/\\`~";
    return strchr(specials, c) != NULL;
}

bool is_password_valid(const char *password)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;
    size_t length;
    size_t i;

    if (password == NULL)
    {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(password);

    if ((length < PASSWORD_MIN_LENGTH) || (length > PASSWORD_MAX_LENGTH))
    {
        return false;
    }

    for (i = 0U; i < length; i++)
    {
        const unsigned char ch = (unsigned char)password[i];

        if (isupper(ch) != 0)
        {
            has_upper = true;
        }
        else if (islower(ch) != 0)
        {
            has_lower = true;
        }
        else if (isdigit(ch) != 0)
        {
            has_digit = true;
        }
        else if (is_special_character((char)ch))
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
    char buffer[INPUT_BUFFER_SIZE];
    size_t len;

    printf("Enter password: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);

    if ((len > 0U) && (buffer[len - 1U] == '\n'))
    {
        buffer[len - 1U] = '\0';
    }
    else if (len == (sizeof(buffer) - 1U))
    {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (((ch = getchar()) != '\n') && (ch != EOF))
        {
        }

        fprintf(stderr, "Input too long\n");
        return 1;
    }
    else
    {
    }

    if (is_password_valid(buffer))
    {
        printf("Password is valid\n");
    }
    else
    {
        printf("Password is invalid\n");
    }

    (void)memset(buffer, 0, sizeof(buffer));

    return 0;
}