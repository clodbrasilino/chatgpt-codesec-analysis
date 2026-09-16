#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    REMOVE_PARENTHESES_OK,
    REMOVE_PARENTHESES_INVALID_ARGUMENT,
    REMOVE_PARENTHESES_UNBALANCED
} RemoveParenthesesResult;

RemoveParenthesesResult remove_parenthesis_areas(char *string)
{
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;

    if (string == NULL) {
        return REMOVE_PARENTHESES_INVALID_ARGUMENT;
    }

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        if (string[read_index] == '(') {
            ++depth;
        } else if (string[read_index] == ')') {
            if (depth == 0) {
                return REMOVE_PARENTHESES_UNBALANCED;
            }
            --depth;
        }
    }

    if (depth != 0) {
        return REMOVE_PARENTHESES_UNBALANCED;
    }

    depth = 0;

    for (read_index = 0; string[read_index] != '\0'; ++read_index) {
        if (string[read_index] == '(') {
            ++depth;
        } else if (string[read_index] == ')') {
            --depth;
        } else if (depth == 0) {
            string[write_index++] = string[read_index];
        }
    }

    string[write_index] = '\0';
    return REMOVE_PARENTHESES_OK;
}

int main(int argc, char *argv[])
{
    RemoveParenthesesResult result;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s \"string\"\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    result = remove_parenthesis_areas(argv[1]);

    if (result != REMOVE_PARENTHESES_OK) {
        if (fputs("Error: invalid or unbalanced parentheses\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}