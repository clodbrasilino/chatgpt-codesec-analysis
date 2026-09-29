#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_EMAIL_LENGTH = 320
};

static bool is_valid_email(const char *email)
{
    static const char pattern[] =
        "^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@"
        "[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?"
        "(\\.[A-Za-z0-9]([A-Za-z0-9-]*[A-Za-z0-9])?)+$";
    regex_t regex;

    if (email == NULL || email[0] == '\0') {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

static bool discard_line(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return true;
        }
    }

    return feof(stdin) != 0;
}

static bool read_email(char **email)
{
    char *buffer;
    size_t capacity = (size_t)MAX_EMAIL_LENGTH + 2U;

    if (email == NULL) {
        return false;
    }

    *email = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return false;
    }

    size_t length = strcspn(buffer, "\n");

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (!feof(stdin)) {
        (void)discard_line();
        free(buffer);
        return false;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[--length] = '\0';
    }

    if (length > (size_t)MAX_EMAIL_LENGTH) {
        free(buffer);
        return false;
    }

    *email = buffer;
    return true;
}

int main(void)
{
    char *email = NULL;

    if (!read_email(&email)) {
        return EXIT_FAILURE;
    }

    puts(is_valid_email(email) ? "Valid" : "Invalid");
    free(email);

    return EXIT_SUCCESS;
}