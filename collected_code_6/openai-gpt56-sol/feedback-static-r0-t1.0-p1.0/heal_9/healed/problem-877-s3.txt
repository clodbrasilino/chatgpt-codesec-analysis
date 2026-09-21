#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_CAPACITY 4096U

static int compare_chars(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a > b) - (a < b);
}

static int sort_string(char *string, size_t length)
{
    if (string == NULL) {
        return -1;
    }

    qsort(string, length, sizeof(*string), compare_chars);
    return 0;
}

static int discard_line(FILE *stream)
{
    char buffer[256];

    if (stream == NULL) {
        return -1;
    }

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_CAPACITY, stdin) == NULL) {
        const int status = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return status;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        char remainder[2];

        if (fgets(remainder, sizeof remainder, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
        } else if (remainder[0] != '\n') {
            if (discard_line(stdin) != 0) {
                free(input);
                return EXIT_FAILURE;
            }

            free(input);
            return EXIT_FAILURE;
        }
    }

    if (sort_string(input, length) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}