#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_numbers_and_positions(const char *text)
{
    size_t i = 0;

    while (text[i] != '\0') {
        if (isdigit((unsigned char)text[i])) {
            const size_t start = i;

            while (isdigit((unsigned char)text[i])) {
                ++i;
            }

            printf("Number: %.*s, Position: %zu\n",
                   (int)(i - start), text + start, start);
        } else {
            ++i;
        }
    }
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }

    print_numbers_and_positions(input);
    free(input);

    return EXIT_SUCCESS;
}