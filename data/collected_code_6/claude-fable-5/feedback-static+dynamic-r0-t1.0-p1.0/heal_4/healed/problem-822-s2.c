#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 64
#define BUFFER_SIZE (MAX_PASSWORD_LENGTH + 2)
#define MAX_DISCARD_CHARS 4096

bool is_valid_password(const char *password);
static bool read_line(char *buffer, size_t size);
static void clear_buffer(char *buffer, size_t size);

bool is_valid_password(const char *password)
{
    size_t length;
    size_t i;
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL) {
        return false;
    }

    length = strnlen(password, (size_t)MAX_PASSWORD_LENGTH + 1U);

    if ((length < (size_t)MIN_PASSWORD_LENGTH) ||
        (length > (size_t)MAX_PASSWORD_LENGTH)) {
        return false;
    }

    for (i = 0U; i < length; i++) {
        unsigned char c = (unsigned char)password[i];

        if (isupper(c) != 0) {
            has_upper = true;
        } else if (islower(c) != 0) {
            has_lower = true;
        } else if (isdigit(c) != 0) {
            has_digit = true;
        } else if (ispunct(c) != 0) {
            has_special = true;
        } else {
            return false;
        }
    }

    return (has_upper && has_lower && has_digit && has_special);
}

static bool read_line(char *buffer, size_t size)
{
    size_t length;
    bool truncated = false;

    if ((buffer == NULL) || (size < 2U)) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    buffer[size - 1U] = '\0';
    length = strnlen(buffer, size);

    if ((length > 0U) && (buffer[length - 1U] == '\n')) {
        buffer[length - 1U] = '\0';
    } else if (length == (size - 1U)) {
        int ch;
        size_t discarded = 0U;

        truncated = true;

        do {
            ch = getchar();
            discarded++;
        } while ((ch != EOF) && (ch != '\n') &&
                 (discarded < (size_t)MAX_DISCARD_CHARS));

        if ((ch != EOF) && (ch != '\n')) {
            clearerr(stdin);
        }
    } else {
        ;
    }

    if (truncated) {
        buffer[0] = '\0';
    }

    return true;
}

static void clear_buffer(char *buffer, size_t size)
{
    volatile char *p = (volatile char *)buffer;
    size_t i;

    if (buffer == NULL) {
        return;
    }

    for (i = 0U; i < size; i++) {
        p[i] = '\0';
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE] = { 0 };
    int result = EXIT_SUCCESS;

    if (printf("Enter password: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (!read_line(buffer, sizeof(buffer))) {
        (void)fprintf(stderr, "Error reading input.\n");
        clear_buffer(buffer, sizeof(buffer));
        return EXIT_FAILURE;
    }

    if (is_valid_password(buffer)) {
        if (printf("Password is valid.\n") < 0) {
            result = EXIT_FAILURE;
        }
    } else {
        if (printf("Password is invalid.\n") < 0) {
            result = EXIT_FAILURE;
        }
    }

    clear_buffer(buffer, sizeof(buffer));

    return result;
}