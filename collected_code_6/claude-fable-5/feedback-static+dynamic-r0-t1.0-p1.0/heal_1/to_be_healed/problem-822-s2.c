#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 64
#define BUFFER_SIZE (MAX_PASSWORD_LENGTH + 2)

bool is_valid_password(const char *password);

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

    length = strnlen(password, MAX_PASSWORD_LENGTH + 1);

    if ((length < MIN_PASSWORD_LENGTH) || (length > MAX_PASSWORD_LENGTH)) {
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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *newline;

    if (printf("Enter password: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while ((ch != '\n') && (ch != EOF));
    }

    if (is_valid_password(buffer)) {
        if (printf("Password is valid.\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Password is invalid.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}