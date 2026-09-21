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
        int first;

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
        first = tolower((int)start[0]);

        if (first == 'a' || first == 'e') {
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

    for (;;) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                goto cleanup;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length > SIZE_MAX - 2U) {
            goto cleanup;
        }

        if (capacity < length + 2U) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *temporary;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else if (capacity <= SIZE_MAX / 2U) {
                new_capacity = capacity * 2U;
            } else {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(line, new_capacity);
            if (temporary == NULL) {
                goto cleanup;
            }

            line = temporary;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            goto cleanup;
        }
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