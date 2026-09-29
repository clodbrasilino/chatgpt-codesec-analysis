#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_chars(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a > b) - (a < b);
}

static int sort_string(char *string)
{
    if (string == NULL) {
        return -1;
    }

    qsort(string, strlen(string), sizeof(*string), compare_chars);
    return 0;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof(input) - 1U) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (sort_string(input) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}