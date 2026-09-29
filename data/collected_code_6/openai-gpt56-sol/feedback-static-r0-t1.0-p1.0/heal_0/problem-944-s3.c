#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_numbers_and_positions(const char *text)
{
    size_t i;

    if (text == NULL) {
        return;
    }

    for (i = 0; text[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)text[i];

        if (isdigit(ch) != 0) {
            printf("Number: %c, Position: %zu\n", text[i], i);
        }
    }
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[(size_t)length - 1U] == '\n') {
        line[(size_t)length - 1U] = '\0';
    }

    print_numbers_and_positions(line);
    free(line);

    return EXIT_SUCCESS;
}