#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool string_starts_with_number(const char *str, int number)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char prefix[32];
    int written;
    size_t prefix_len;

    if (str == NULL) {
        return false;
    }

    written = snprintf(prefix, sizeof(prefix), "%d", number);
    if (written < 0 || (size_t)written >= sizeof(prefix)) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    prefix_len = strlen(prefix);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(str) < prefix_len) {
        return false;
    }

    return strncmp(str, prefix, prefix_len) == 0;
}

int main(void)
{
    const char *test1 = "42 is the answer";
    const char *test2 = "hello world";
    const char *test3 = "100 percent";
    int result_status = EXIT_SUCCESS;

    if (string_starts_with_number(test1, 42)) {
        if (printf("\"%s\" starts with 42\n", test1) < 0) {
            result_status = EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with 42\n", test1) < 0) {
            result_status = EXIT_FAILURE;
        }
    }

    if (string_starts_with_number(test2, 7)) {
        if (printf("\"%s\" starts with 7\n", test2) < 0) {
            result_status = EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with 7\n", test2) < 0) {
            result_status = EXIT_FAILURE;
        }
    }

    if (string_starts_with_number(test3, 100)) {
        if (printf("\"%s\" starts with 100\n", test3) < 0) {
            result_status = EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with 100\n", test3) < 0) {
            result_status = EXIT_FAILURE;
        }
    }

    return result_status;
}