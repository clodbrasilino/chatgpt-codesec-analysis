#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    REMOVE_SUCCESS = 0,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_UNBALANCED_PARENTHESES,
    REMOVE_ALLOCATION_FAILURE
} RemoveStatus;

RemoveStatus remove_parenthesized(const char *input, char **output)
{
    size_t read_index;
    size_t write_index = 0;
    size_t output_length = 0;
    size_t depth = 0;
    char *result;

    if (output == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    for (read_index = 0; input[read_index] != '\0'; ++read_index) {
        if (input[read_index] == '(') {
            if (depth == SIZE_MAX) {
                return REMOVE_INVALID_ARGUMENT;
            }
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0) {
                return REMOVE_UNBALANCED_PARENTHESES;
            }
            --depth;
        } else if (depth == 0) {
            if (output_length == SIZE_MAX) {
                return REMOVE_INVALID_ARGUMENT;
            }
            ++output_length;
        }
    }

    if (depth != 0) {
        return REMOVE_UNBALANCED_PARENTHESES;
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        return REMOVE_ALLOCATION_FAILURE;
    }

    depth = 0;

    for (read_index = 0; input[read_index] != '\0'; ++read_index) {
        if (input[read_index] == '(') {
            ++depth;
        } else if (input[read_index] == ')') {
            --depth;
        } else if (depth == 0) {
            result[write_index++] = input[read_index];
        }
    }

    result[write_index] = '\0';
    *output = result;

    return REMOVE_SUCCESS;
}

int main(int argc, char **argv)
{
    const char *program_name;
    char *result = NULL;
    RemoveStatus status;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"text\"\n", program_name);
        return EXIT_FAILURE;
    }

    status = remove_parenthesized(argv[1], &result);

    switch (status) {
        case REMOVE_SUCCESS:
            break;

        case REMOVE_ALLOCATION_FAILURE:
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;

        case REMOVE_UNBALANCED_PARENTHESES:
            fputs("The input contains unbalanced parentheses.\n", stderr);
            return EXIT_FAILURE;

        case REMOVE_INVALID_ARGUMENT:
        default:
            fputs("Invalid argument.\n", stderr);
            return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}