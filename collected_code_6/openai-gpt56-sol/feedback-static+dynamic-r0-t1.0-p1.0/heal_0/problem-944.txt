#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void print_numbers_and_positions(const char *string)
{
    size_t index = 0;

    while (string[index] != '\0') {
        if (isdigit((unsigned char)string[index])) {
            size_t start = index;

            while (isdigit((unsigned char)string[index])) {
                index++;
            }

            printf("Number: %.*s, Position: %zu\n",
                   (int)(index - start), string + start, start);
        } else {
            index++;
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    print_numbers_and_positions(line);
    free(line);

    return EXIT_SUCCESS;
}