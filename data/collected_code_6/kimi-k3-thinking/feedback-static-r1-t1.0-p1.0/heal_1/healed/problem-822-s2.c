#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PASSWORD_MIN_LENGTH 8U
#define PASSWORD_MAX_LENGTH 64U
#define INPUT_BUFFER_SIZE   128
#define MAX_DISCARD_COUNT   1024U

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0U;

    if (s == NULL)
    {
        return 0U;
    }

    while ((len < max_len) && (s[len] != '\0'))
    {
        len++;
    }

    return len;
}

static bool is_special_character(char c)
{
    const char *specials = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/\\`~";

    if (c == '\0')
    {
        return false;
    }

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

    length = bounded_strlen(password, PASSWORD_MAX_LENGTH + 1U);

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
    char buffer[INPUT_BUFFER_SIZE] = {0};
    size_t len;

    printf("Enter password: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = bounded_strlen(buffer, sizeof(buffer));

    if ((len > 0U) && (buffer[len - 1U] == '\n'))
    {
        buffer[len - 1U] = '\0';
    }
    else if (len == (sizeof(buffer) - 1U))
    {
        int ch;
        size_t discarded = 0U;

        while ((discarded < MAX_DISCARD_COUNT) && ((ch = getchar()) != '\n') && (ch != EOF))
        {
            discarded++;
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