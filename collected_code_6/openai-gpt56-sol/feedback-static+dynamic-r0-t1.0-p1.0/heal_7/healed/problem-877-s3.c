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

    while ((ch = fgetc(stream)) != '\n') {
        if (ch == EOF) {
            return ferror(stream) ? -1 : 0;
        }
    }

    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U) {
        int next = fgetc(stdin);

        if (next == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
        } else if (next != '\n') {
            if (discard_line(stdin) != 0) {
                return EXIT_FAILURE;
            }

            return EXIT_FAILURE;
        }
    }

    sort_string(input, length);

    if (fwrite(input, sizeof input[0], length, stdout) != length) {
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}