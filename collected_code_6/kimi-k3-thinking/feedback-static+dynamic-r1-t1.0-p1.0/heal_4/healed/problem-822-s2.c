#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PASSWORD_MIN_LENGTH 8U
#define PASSWORD_MAX_LENGTH 64U
#define INPUT_BUFFER_SIZE   (PASSWORD_MAX_LENGTH + 2U)
#define MAX_DISCARD_CHARS   1024U

_Static_assert(INPUT_BUFFER_SIZE > (PASSWORD_MAX_LENGTH + 1U),
               "Input buffer must hold max password plus newline and NUL terminator");

static size_t safe_string_length(const char *s, size_t max_length)
{
    size_t length = 0U;

    if (s == NULL)
    {
        return 0U;
    }

    while ((length < max_length) && (s[length] != '\0'))
    {
        length++;
    }

    return length;
}

static void secure_clear(void *ptr, size_t size)
{
    volatile unsigned char *p = (volatile unsigned char *)ptr;

    while (size > 0U)
    {
        *p = 0U;
        p++;
        size--;
    }
}

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

    length = safe_string_length(password, PASSWORD_MAX_LENGTH + 1U);

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

static void discard_remaining_input(void)
{
    size_t discarded = 0U;
    int ch = EOF;

    while (discarded < MAX_DISCARD_CHARS)
    {
        ch = getchar();

        if ((ch == '\n') || (ch == EOF))
        {
            break;
        }

        discarded++;
    }
}

int main(void)
{
    char buffer[INPUT_BUFFER_SIZE];
    size_t len;

    (void)memset(buffer, 0, sizeof(buffer));

    printf("Enter password: ");
    (void)fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        secure_clear(buffer, sizeof(buffer));
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = safe_string_length(buffer, sizeof(buffer));

    if ((len > 0U) && (buffer[len - 1U] == '\n'))
    {
        buffer[len - 1U] = '\0';
    }
    else if (len == (sizeof(buffer) - 1U))
    {
        discard_remaining_input();
        fprintf(stderr, "Input too long\n");
        secure_clear(buffer, sizeof(buffer));
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

    secure_clear(buffer, sizeof(buffer));

    return 0;
}