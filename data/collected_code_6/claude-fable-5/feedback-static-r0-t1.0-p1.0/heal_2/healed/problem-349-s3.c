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
        ch = getchar();
    } while ((ch != '\n') && (ch != EOF));
}

int main(void)
{
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