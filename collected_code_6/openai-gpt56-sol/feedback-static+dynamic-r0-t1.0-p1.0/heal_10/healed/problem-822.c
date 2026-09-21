#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128,
    INPUT_BUFFER_SIZE = MAX_PASSWORD_LENGTH + 2
};

static bool is_valid_password(const char *password, size_t length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < MIN_PASSWORD_LENGTH ||
        length > MAX_PASSWORD_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        const unsigned char character = (unsigned char)password[i];

        if (character >= (unsigned char)'A' &&
            character <= (unsigned char)'Z') {
            has_upper = true;
        } else if (character >= (unsigned char)'a' &&
                   character <= (unsigned char)'z') {
            has_lower = true;
        } else if (character >= (unsigned char)'0' &&
                   character <= (unsigned char)'9') {
            has_digit = true;
        } else if (character >= 33U && character <= 126U) {
            has_special = true;
        } else {
            return false;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

static int discard_line(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_password(char **password, size_t *length)
{
    char *buffer;
    size_t used;

    if (password == NULL || length == NULL) {
        return -1;
    }

    *password = NULL;
    *length = 0;

    buffer = malloc(INPUT_BUFFER_SIZE);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, INPUT_BUFFER_SIZE, stdin) == NULL) {
        free(buffer);
        return -1;
    }

    used = strcspn(buffer, "\n");

    if (buffer[used] == '\n') {
        buffer[used] = '\0';
    } else if (!feof(stdin)) {
        const int discard_status = discard_line();
        free(buffer);
        return discard_status < 0 ? -1 : 0;
    }

    if (used > 0 && buffer[used - 1] == '\r') {
        buffer[--used] = '\0';
    }

    if (used > MAX_PASSWORD_LENGTH) {
        free(buffer);
        return 0;
    }

    {
        char *resized = realloc(buffer, used + 1);
        if (resized != NULL) {
            buffer = resized;
        }
    }

    *password = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *password = NULL;
    size_t length = 0;
    const int status = read_password(&password, &length);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        puts("false");
        return EXIT_SUCCESS;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    free(password);

    return EXIT_SUCCESS;
}