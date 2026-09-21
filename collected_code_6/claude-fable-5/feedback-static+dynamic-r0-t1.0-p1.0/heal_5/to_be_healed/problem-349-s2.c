#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256U

static bool is_binary_string(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0U; (i < max_len) && (str[i] != '\0'); i++) {
        if ((str[i] != '0') && (str[i] != '1')) {
            return false;
        }
    }

    if (i >= max_len) {
        return false;
    }

    return true;
}

static void flush_stdin(void)
{
    int c;
    size_t count = 0U;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
        count++;
    } while ((c != '\n') && (c != EOF) && (count < 1000000U));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t len;
    char *newline;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    newline = memchr(buffer, '\n', sizeof(buffer));
    if (newline != NULL) {
        *newline = '\0';
    } else {
        len = strnlen(buffer, sizeof(buffer));
        if (len == (sizeof(buffer) - 1U)) {
            flush_stdin();
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len >= sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (is_binary_string(buffer, sizeof(buffer))) {
        printf("The string is a binary string\n");
    } else {
        printf("The string is not a binary string\n");
    }

    return EXIT_SUCCESS;
}