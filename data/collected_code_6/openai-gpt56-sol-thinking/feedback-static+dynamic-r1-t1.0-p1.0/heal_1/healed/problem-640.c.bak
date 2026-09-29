#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    REMOVE_SUCCESS = 0,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_UNBALANCED_PARENTHESES,
    REMOVE_ALLOCATION_FAILURE
} RemoveStatus;

RemoveStatus remove_parenthesized(const char *input, char **output)
{
    size_t length;
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *output = NULL;
    length = strlen(input);
    result = malloc(length + 1);

    if (result == NULL) {
        return REMOVE_ALLOCATION_FAILURE;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        if (input[read_index] == '(') {
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0) {
                free(result);
                return REMOVE_UNBALANCED_PARENTHESES;
            }

            --depth;
        } else if (depth == 0) {
            result[write_index++] = input[read_index];
        }
    }

    if (depth != 0) {
        free(result);
        return REMOVE_UNBALANCED_PARENTHESES;
    }

    result[write_index] = '\0';
    *output = result;

    return REMOVE_SUCCESS;
}

int main(int argc, char *argv[const])
{
    const char *program_name;
    char *result = NULL;
    RemoveStatus status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
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

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}