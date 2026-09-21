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
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
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
            free(line);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity = capacity == 0U ? 64U : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = SIZE_MAX;
                    break;
                }
                new_capacity *= 2U;
            }

            if (new_capacity < required) {
                free(line);
                fputs("Input is too large.\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_line = realloc(line, new_capacity);
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

    if (line == NULL) {
        line = malloc(1U);
        if (line == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    line[length] = '\0';
    sort_string(line, length);

    if (fwrite(line, sizeof(*line), length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}