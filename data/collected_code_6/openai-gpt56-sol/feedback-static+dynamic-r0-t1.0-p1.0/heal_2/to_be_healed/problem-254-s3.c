#include <ctype.h>
#include <limits.h>
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
            if (length > (size_t)INT_MAX ||
                printf("%.*s\n", (int)length, (const char *)start) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int status = EXIT_SUCCESS;
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1) {
            status = EXIT_FAILURE;
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = length + 2;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                status = EXIT_FAILURE;
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (line == NULL) {
        line = malloc(1);
        if (line == NULL) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    line[length] = '\0';

    if (print_matching_words(line) != 0) {
        status = EXIT_FAILURE;
    }

cleanup:
    free(line);
    return status;
}