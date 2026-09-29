#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t bounded_strlen(const char *str, size_t capacity)
{
    size_t length = 0;

    while (length < capacity && str[length] != '\0') {
        ++length;
    }

    return length;
}

static int discard_remaining_input(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' ? 0 : -1;
}

static int move_numbers_to_end(char *str, size_t capacity)
{
    char *result;
    size_t length;
    size_t position = 0;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = bounded_strlen(str, capacity);
    if (length == capacity) {
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
    memcpy(str, result, position + 1);
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

    length = bounded_strlen(input, INPUT_CAPACITY);
    if (length == INPUT_CAPACITY) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
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