#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_matching_words(const char *text)
{
    const unsigned char *p;

    if (text == NULL) {
        return -1;
    }

    p = (const unsigned char *)text;

    while (*p != '\0') {
        const unsigned char *start;
        size_t length;

        while (*p != '\0' && !isalpha((int)*p)) {
            ++p;
        }

        if (*p == '\0') {
            break;
        }

        start = p;

        while (*p != '\0' && isalpha((int)*p)) {
            ++p;
        }

        length = (size_t)(p - start);

        if (tolower((int)start[0]) == 'a' || tolower((int)start[0]) == 'e') {
            if (fwrite(start, 1U, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int status = EXIT_FAILURE;
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *new_line;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            goto cleanup;
        }
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = 1U;
    }

    line[length] = '\0';

    if (print_matching_words(line) != 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    return status;
}