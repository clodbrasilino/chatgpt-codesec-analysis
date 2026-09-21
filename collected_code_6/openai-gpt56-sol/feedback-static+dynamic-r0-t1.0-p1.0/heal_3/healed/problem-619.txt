#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int discard_remaining_input(void)
{
    int ch;

    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return -1;
        }
    }

    return 0;
}

static int move_numbers_to_end(char *str, size_t capacity)
{
    size_t length;
    size_t position = 0;
    char *result;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(str, capacity);
    if (length == capacity || length == SIZE_MAX) {
        return -1;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!isdigit((unsigned char)str[i])) {
            result[position++] = str[i];
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (isdigit((unsigned char)str[i])) {
            result[position++] = str[i];
        }
    }

    result[position] = '\0';

    if (position + 1 > capacity) {
        free(result);
        return -1;
    }

    memmove(str, result, position + 1);
    free(result);

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024 };
    char *input;
    size_t length;

    input = malloc(INPUT_CAPACITY);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    length = strnlen(input, INPUT_CAPACITY);
    if (length == INPUT_CAPACITY) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (length == INPUT_CAPACITY - 1) {
        if (discard_remaining_input() != 0) {
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_FAILURE;
    }

    if (move_numbers_to_end(input, INPUT_CAPACITY) != 0) {
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