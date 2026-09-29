#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum {
    MIN_PASSWORD_LENGTH = 8,
    MAX_PASSWORD_LENGTH = 128
};

static bool is_valid_password(const char *password, size_t length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    if (password == NULL ||
        length < (size_t)MIN_PASSWORD_LENGTH ||
        length > (size_t)MAX_PASSWORD_LENGTH) {
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

static int read_password(char **password, size_t *length)
{
    char *buffer;
    size_t used;
    /* Possible weaknesses found:
     *  Unused variable: character [unusedVariable]
     */
    int character;

    if (password == NULL || length == NULL) {
        return -1;
    }

    *password = NULL;
    *length = 0;

    buffer = malloc((size_t)MAX_PASSWORD_LENGTH + 2U);
    if (buffer == NULL) {
        return -1;
    }

    if (fgets(buffer, MAX_PASSWORD_LENGTH + 2, stdin) == NULL) {
        free(buffer);
        return ferror(stdin) ? -1 : 0;
    }

    used = 0;
    while (buffer[used] != '\0' &&
           buffer[used] != '\n' &&
           buffer[used] != '\r') {
        ++used;
    }

    if (buffer[used] == '\0') {
        if (used > (size_t)MAX_PASSWORD_LENGTH) {
            int next;

            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                next = getchar();
            } while (next != '\n' && next != '\r' && next != EOF);

            if (next == '\r') {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                next = getchar();
                if (next != '\n' && next != EOF) {
                    if (ungetc(next, stdin) == EOF) {
                        free(buffer);
                        return -1;
                    }
                }
            }

            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }

            free(buffer);
            return 0;
        }
    } else if (buffer[used] == '\r' && buffer[used + 1U] == '\n') {
        buffer[used + 1U] = '\0';
    }

    buffer[used] = '\0';
    *password = buffer;
    *length = used;

    return 1;
}

int main(void)
{
    char *password = NULL;
    size_t length = 0;
    int result = read_password(&password, &length);

    if (result < 0) {
        free(password);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("false");
        free(password);
        return EXIT_SUCCESS;
    }

    puts(is_valid_password(password, length) ? "true" : "false");
    free(password);

    return EXIT_SUCCESS;
}