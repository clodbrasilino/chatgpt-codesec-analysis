#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_matching_positions(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    for (size_t i = 0; i < 26 && str[i] != '\0'; ++i) {
        unsigned char ch = (unsigned char)str[i];

        if (isalpha(ch) && tolower(ch) == 'a' + (int)i) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t available = capacity - length;
        size_t request = available > (size_t)INT_MAX
                       ? (size_t)INT_MAX
                       : available;

        if (request < 2) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
            continue;
        }

        if (fgets(input + length, (int)request, stdin) == NULL) {
            break;
        }

        while (input[length] != '\0' && input[length] != '\n') {
            ++length;
        }

        if (input[length] == '\n') {
            input[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (printf("%zu\n", count_matching_positions(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}