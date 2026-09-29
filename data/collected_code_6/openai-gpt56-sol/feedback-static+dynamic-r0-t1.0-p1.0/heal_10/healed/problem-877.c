#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compare_chars(const void *lhs, const void *rhs)
{
    const unsigned char a = *(const unsigned char *)lhs;
    const unsigned char b = *(const unsigned char *)rhs;

    return (a > b) - (a < b);
}

static void sort_string(char *str, size_t length)
{
    if (str != NULL && length > 1U) {
        qsort(str, length, sizeof(*str), compare_chars);
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            free(line);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(line);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                fputs("Memory allocation failed.\n", stderr);
                return EXIT_FAILURE;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(line);
        fputs("Input error.\n", stderr);
        return EXIT_FAILURE;
    }

    sort_string(line, length);

    if ((length > 0U &&
         fwrite(line, sizeof(*line), length, stdout) != length) ||
        fputc('\n', stdout) == EOF) {
        free(line);
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}