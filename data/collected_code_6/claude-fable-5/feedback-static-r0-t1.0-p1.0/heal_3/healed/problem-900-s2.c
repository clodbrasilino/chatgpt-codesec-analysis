#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool string_starts_with_number(const char *str, int number)
{
    char *prefix;
    int required;
    int written;
    size_t prefix_len;
    bool matches;

    if (str == NULL) {
        return false;
    }

    required = snprintf(NULL, 0, "%d", number);
    if (required < 0) {
        return false;
    }

    prefix = malloc((size_t)required + 1);
    if (prefix == NULL) {
        return false;
    }

    written = snprintf(prefix, (size_t)required + 1, "%d", number);
    if (written < 0 || written != required) {
        free(prefix);
        return false;
    }

    prefix_len = (size_t)written;
    matches = (strncmp(str, prefix, prefix_len) == 0);

    free(prefix);
    return matches;
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