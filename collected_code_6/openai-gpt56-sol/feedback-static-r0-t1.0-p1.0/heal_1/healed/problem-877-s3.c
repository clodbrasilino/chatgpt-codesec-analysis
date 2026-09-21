#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_CAPACITY, stdin) == NULL) {
        int result = ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
        free(input);
        return result;
    }

    size_t length = 0U;

    while (length < INPUT_CAPACITY && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < INPUT_CAPACITY && input[length] == '\n') {
        input[length] = '\0';
    } else {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            free(input);
            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (sort_string(input, length) != 0 || puts(input) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}