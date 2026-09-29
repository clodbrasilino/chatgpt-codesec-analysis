#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { INPUT_CAPACITY = 4096 };

static int compare_chars(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a > b) - (a < b);
}

static void sort_string(char *string, size_t length)
{
    qsort(string, length, sizeof *string, compare_chars);
}

static int discard_line(FILE *stream)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stream) ? -1 : 0;
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == INPUT_CAPACITY - 1U) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
        } else if (next != '\n') {
            if (discard_line(stdin) != 0) {
                free(input);
                return EXIT_FAILURE;
            }

            free(input);
            return EXIT_FAILURE;
        }
    }

    sort_string(input, length);

    if (fwrite(input, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}