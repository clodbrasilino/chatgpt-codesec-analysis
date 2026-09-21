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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *result = NULL;
    RemoveStatus status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = remove_parenthesized(argv[1], &result);

    if (status == REMOVE_ALLOCATION_FAILURE) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == REMOVE_UNBALANCED_PARENTHESES) {
        fputs("The input contains unbalanced parentheses.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != REMOVE_SUCCESS) {
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