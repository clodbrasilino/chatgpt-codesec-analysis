#include <ctype.h>
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

        while (*p != '\0' && !isalpha(*p)) {
            ++p;
        }

        if (*p == '\0') {
            break;
        }

        start = p;

        while (*p != '\0' && isalpha(*p)) {
            ++p;
        }

        length = (size_t)(p - start);

        if (tolower(start[0]) == 'a' || tolower(start[0]) == 'e') {
            if (printf("%.*s\n", (int)length, (const char *)start) < 0) {
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
    int ch;
    int status = EXIT_SUCCESS;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *new_line;

            if (new_capacity <= capacity) {
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

        line[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (line == NULL) {
        line = malloc(1U);
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