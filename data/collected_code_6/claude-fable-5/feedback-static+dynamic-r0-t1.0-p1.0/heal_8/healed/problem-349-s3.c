#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 256U
#define FLUSH_GUARD_LIMIT 1000000U

static bool is_binary_string(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
        if ((str[i] != '0') && (str[i] != '1')) {
            return false;
        }
    }

    if (i >= max_len) {
        return false;
    }

    return true;
}

static size_t safe_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0U;
    }

    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0U;

    do {
        ch = fgetc(stdin);
        guard++;
        if (guard > (size_t)FLUSH_GUARD_LIMIT) {
            break;
        }
    } while ((ch != '\n') && (ch != EOF));
}

int main(void)
{
    char input[MAX_INPUT_LENGTH];
    size_t len;

    (void)memset(input, 0, sizeof(input));

    printf("Enter a string: ");
    (void)fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    len = safe_strlen(input, sizeof(input));

    if ((len > 0U) && (input[len - 1U] == '\n')) {
        input[len - 1U] = '\0';
    } else if (len == (sizeof(input) - 1U)) {
        flush_stdin();
    } else {
    }

    if (is_binary_string(input, sizeof(input))) {
        printf("The string is a binary string.\n");
    } else {
        printf("The string is not a binary string.\n");
    }

    return EXIT_SUCCESS;
}