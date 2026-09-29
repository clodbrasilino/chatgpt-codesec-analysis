#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    REMOVE_SUCCESS = 0,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_UNBALANCED_PARENTHESES,
    REMOVE_ALLOCATION_FAILURE
} RemoveStatus;

RemoveStatus remove_parenthesized(const char *input, size_t input_length,
                                  char **output)
{
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;
    char *result;

    if (output == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL || input_length == SIZE_MAX) {
        return REMOVE_INVALID_ARGUMENT;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return REMOVE_ALLOCATION_FAILURE;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *input;
    const char *program_name;
    size_t input_length = 0;
    char *result = NULL;
    RemoveStatus status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"text\"\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            fputs("The input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    status = remove_parenthesized(input, input_length, &result);

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