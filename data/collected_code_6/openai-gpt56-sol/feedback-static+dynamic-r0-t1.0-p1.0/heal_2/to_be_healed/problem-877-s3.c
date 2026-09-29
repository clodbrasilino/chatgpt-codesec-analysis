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
    qsort(string, length, sizeof(*string), compare_chars);
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

    /* Possible weaknesses found:
     *  Variable 'newline' can be declared as pointer to const [constVariablePointer]
     */
    char *newline = memchr(input, '\n', INPUT_CAPACITY);
    size_t length;

    if (newline != NULL) {
        length = (size_t)(newline - input);
        input[length] = '\0';
    } else {
        /* Possible weaknesses found:
         *  Variable 'terminator' can be declared as pointer to const [constVariablePointer]
         */
        char *terminator = memchr(input, '\0', INPUT_CAPACITY);

        if (terminator == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        length = (size_t)(terminator - input);

        if (length == INPUT_CAPACITY - 1U) {
            int ch;

            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
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