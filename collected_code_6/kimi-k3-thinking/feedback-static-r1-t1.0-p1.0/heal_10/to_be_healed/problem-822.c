#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MIN_PASSWORD_LENGTH ((size_t)8)
#define MAX_PASSWORD_LENGTH ((size_t)64)
#define INPUT_BUFFER_SIZE (MAX_PASSWORD_LENGTH + 2)
#define DISCARD_BUFFER_SIZE ((size_t)256)
#define MAX_DISCARD_CHARS ((size_t)4096)

_Static_assert(INPUT_BUFFER_SIZE > MAX_PASSWORD_LENGTH,
               "Input buffer must be larger than the maximum password length");
_Static_assert(INPUT_BUFFER_SIZE <= (size_t)INT_MAX &&
               DISCARD_BUFFER_SIZE <= (size_t)INT_MAX,
               "Buffer sizes must fit in an int for fgets");

bool is_valid_password(const char *password, size_t buffer_size);
static void discard_remaining_line(void);
static void secure_clear(void *buffer, size_t size);

bool is_valid_password(const char *password, size_t buffer_size)
{
    size_t length;
    size_t i;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL || buffer_size == 0)
    {
        return false;
    }

    length = strnlen(password, buffer_size);

    if (length >= buffer_size)
    {
        return false;
    }

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

static void secure_clear(void *buffer, size_t size)
{
    volatile unsigned char *p;

    if (buffer == NULL)
    {
        return;
    }

    p = (volatile unsigned char *)buffer;

    while (size > 0)
    {
        *p = 0;
        p++;
        size--;
    }
}

static void discard_remaining_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char discard_buffer[DISCARD_BUFFER_SIZE] = {0};
    size_t discarded = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'chunk_length' can be reduced. [variableScope]
     */
    size_t chunk_length;

    while (discarded < MAX_DISCARD_CHARS)
    {
        if (fgets(discard_buffer, (int)sizeof(discard_buffer), stdin) == NULL)
        {
            break;
        }

        discard_buffer[sizeof(discard_buffer) - 1] = '\0';
        chunk_length = strnlen(discard_buffer, sizeof(discard_buffer));

        if (chunk_length > 0 && discard_buffer[chunk_length - 1] == '\n')
        {
            break;
        }

        discarded += chunk_length;
    }

    secure_clear(discard_buffer, sizeof(discard_buffer));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char password[INPUT_BUFFER_SIZE] = {0};
    size_t input_length;

    printf("Enter password: ");
    fflush(stdout);

    if (fgets(password, (int)sizeof(password), stdin) == NULL)
    {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    password[sizeof(password) - 1] = '\0';

    input_length = strnlen(password, sizeof(password));

    if (input_length == 0 || input_length >= sizeof(password))
    {
        fprintf(stderr, "Input error.\n");
        secure_clear(password, sizeof(password));
        return EXIT_FAILURE;
    }

    if (password[input_length - 1] == '\n')
    {
        password[input_length - 1] = '\0';
    }
    else if (input_length == sizeof(password) - 1)
    {
        discard_remaining_line();
        printf("Password is invalid.\n");
        secure_clear(password, sizeof(password));
        return EXIT_SUCCESS;
    }

    if (is_valid_password(password, sizeof(password)))
    {
        printf("Password is valid.\n");
    }
    else
    {
        printf("Password is invalid.\n");
    }

    secure_clear(password, sizeof(password));

    return EXIT_SUCCESS;
}