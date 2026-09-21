#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_first_and_last(char *str, size_t length, char target)
{
    size_t first = length;
    size_t last = length;

    if (str == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == target) {
            if (first == length) {
                first = i;
            }
            last = i;
        }
    }

    if (first == length) {
        return 0;
    }

    if (first == last) {
        memmove(str + first, str + first + 1, length - first);
        return 1;
    }

    memmove(str + last, str + last + 1, length - last);
    memmove(str + first, str + first + 1, length - first - 1);

    return 2;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    int target;
    int extra;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0 ? 1 : capacity + 1;
        char *new_input;

        if (new_capacity <= capacity) {
            free(input);
            return EXIT_FAILURE;
        }

        new_input = realloc(input, new_capacity);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = new_capacity;
    }

    input[length] = '\0';

    target = getchar();
    if (target == '\n' || target == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    extra = getchar();
    if (extra != '\n' && extra != EOF) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        free(input);
        return EXIT_FAILURE;
    }

    if (remove_first_and_last(input, length, (char)target) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", input) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}