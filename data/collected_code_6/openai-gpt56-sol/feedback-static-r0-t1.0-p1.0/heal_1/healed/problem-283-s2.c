#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static int frequencies_are_valid(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || *input == '\0') {
        return 0;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (!isdigit(*p)) {
            return 0;
        }

        unsigned int digit = (unsigned int)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return 0;
        }

        ++frequencies[digit];
    }

    return 1;
}

int main(void)
{
    size_t capacity = 64;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return EXIT_FAILURE;
    }

    int ch;
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                fputs("Input too long\n", stderr);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                fputs("Memory allocation error\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    input[length] = '\0';
    puts(frequencies_are_valid(input) ? "true" : "false");

    free(input);
    return EXIT_SUCCESS;
}