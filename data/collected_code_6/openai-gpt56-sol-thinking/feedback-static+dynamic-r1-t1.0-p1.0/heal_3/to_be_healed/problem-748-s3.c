#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *insert_spaces_before_capitals(const char *input)
{
    const unsigned char *cursor;
    const unsigned char *start;
    char *result;
    char *destination;
    size_t output_length = 0;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    start = (const unsigned char *)input;
    cursor = start;

    while (*cursor != '\0') {
        size_t required = 1;

        if (cursor != start &&
            isupper(*cursor) &&
            !isspace(cursor[-1])) {
            required = 2;
        }

        if (output_length > SIZE_MAX - required) {
            errno = EOVERFLOW;
            return NULL;
        }

        output_length += required;
        ++cursor;
    }

    if (output_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    cursor = start;
    destination = result;

    while (*cursor != '\0') {
        if (cursor != start &&
            isupper(*cursor) &&
            !isspace(cursor[-1])) {
            *destination++ = ' ';
        }

        *destination++ = (char)*cursor++;
    }

    *destination = '\0';
    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name;
    char *result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(argv[1]);
    if (result == NULL) {
        perror("insert_spaces_before_capitals");
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        perror("output");
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}