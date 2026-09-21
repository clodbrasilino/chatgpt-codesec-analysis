#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define PASSWORD_MIN_LENGTH 8U
#define PASSWORD_MAX_LENGTH 64U
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

static void discard_remaining_input(void)
{
    char discard_buffer[MAX_DISCARD_COUNT + 1U];
    size_t len;

    while (fgets(discard_buffer, (int)sizeof(discard_buffer), stdin) != NULL)
    {
        len = bounded_strlen(discard_buffer, sizeof(discard_buffer));

        if ((len > 0U) && (discard_buffer[len - 1U] == '\n'))
        {
            break;
        }
    }
}

int main(void)
{
    const size_t buffer_size = PASSWORD_MAX_LENGTH + 2U;
    char *buffer = calloc(buffer_size, sizeof(char));
    size_t len;

    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter password: ");

    if (fgets(buffer, (int)buffer_size, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        (void)memset(buffer, 0, buffer_size);
        free(buffer);
        return 1;
    }

    buffer[buffer_size - 1U] = '\0';

    len = bounded_strlen(buffer, buffer_size);

    if ((len > 0U) && (buffer[len - 1U] == '\n'))
    {
        buffer[len - 1U] = '\0';
    }
    else if (len == (buffer_size - 1U))
    {
        discard_remaining_input();
        fprintf(stderr, "Input too long\n");
        (void)memset(buffer, 0, buffer_size);
        free(buffer);
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

    (void)memset(buffer, 0, buffer_size);
    free(buffer);

    return 0;
}