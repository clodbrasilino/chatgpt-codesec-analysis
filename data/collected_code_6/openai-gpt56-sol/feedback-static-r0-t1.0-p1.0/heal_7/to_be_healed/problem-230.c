#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(FILE *stream)
{
    if (stream == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    while (fgets(buffer, (int)sizeof(buffer), stream) != NULL) {
        if (strchr(buffer, '\n') != NULL) {
            return 0;
        }
    }

    return ferror(stream) ? -1 : 0;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)INPUT_SIZE, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        if (discard_line(stdin) != 0) {
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_FAILURE;
    } else if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char replacement_buffer[3];

    if (fgets(replacement_buffer, (int)sizeof(replacement_buffer), stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    if (replacement_buffer[0] == '\0' || replacement_buffer[0] == '\n') {
        free(input);
        return EXIT_FAILURE;
    }

    if (replacement_buffer[1] != '\n' && replacement_buffer[1] != '\0') {
        if (discard_line(stdin) != 0) {
            free(input);
            return EXIT_FAILURE;
        }

        free(input);
        return EXIT_FAILURE;
    }

    if (replace_spaces(input, length, replacement_buffer[0]) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (fwrite(input, 1U, length, stdout) != length ||
        fputc('\n', stdout) == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}