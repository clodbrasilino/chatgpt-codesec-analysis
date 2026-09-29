#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 256U

static bool is_binary_string(const char *str)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0U; str[i] != '\0'; i++) {
        if ((str[i] != '0') && (str[i] != '1')) {
            return false;
        }
    }

    return true;
}

static void flush_stdin(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while ((ch != '\n') && (ch != EOF));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH];
    size_t len;
    char *newline;
    bool truncated;

    (void)memset(input, 0, sizeof(input));

    printf("Enter a string: ");
    (void)fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    truncated = true;
    newline = memchr(input, '\n', sizeof(input));
    if (newline != NULL) {
        *newline = '\0';
        truncated = false;
    }

    len = strnlen(input, sizeof(input));
    if (truncated && (len >= (sizeof(input) - 1U))) {
        flush_stdin();
    }

    if (is_binary_string(input)) {
        printf("The string is a binary string.\n");
    } else {
        printf("The string is not a binary string.\n");
    }

    return EXIT_SUCCESS;
}