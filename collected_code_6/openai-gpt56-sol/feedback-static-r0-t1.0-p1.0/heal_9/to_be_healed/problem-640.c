#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1024 * 1024 };

static int remove_parenthesized(const char *input, size_t length, char **output)
{
    char *result;
    size_t read_index;
    size_t write_index = 0;
    size_t depth = 0;

    if (input == NULL || output == NULL || length > (size_t)MAX_INPUT_LENGTH) {
        return -1;
    }

    *output = NULL;

    if (length == SIZE_MAX) {
        return -1;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < length; ++read_index) {
        if (input[read_index] == '(') {
            if (depth == SIZE_MAX) {
                free(result);
                return -1;
            }
            ++depth;
        } else if (input[read_index] == ')') {
            if (depth == 0) {
                free(result);
                return -1;
            }
            --depth;
        } else if (depth == 0) {
            result[write_index++] = input[read_index];
        }
    }

    if (depth != 0) {
        free(result);
        return -1;
    }

    result[write_index] = '\0';
    *output = result;
    return 0;
}

static int discard_remaining_line(FILE *stream)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[4096];

    while (fgets(buffer, sizeof buffer, stream) != NULL) {
        size_t i;

        for (i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                return 0;
            }
        }
    }

    return ferror(stream) ? -1 : 0;
}

static int read_line(char **line, size_t *length)
{
    char *buffer;
    size_t used = 0;
    int found_newline = 0;

    if (line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return -1;
    }

    while (used < (size_t)MAX_INPUT_LENGTH) {
        size_t remaining = (size_t)MAX_INPUT_LENGTH - used;
        size_t chunk_size = remaining + 1U;
        size_t i;

        if (chunk_size > 4096U) {
            chunk_size = 4096U;
        }

        if (fgets(buffer + used, (int)chunk_size, stdin) == NULL) {
            if (ferror(stdin) || used == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        for (i = 0; buffer[used + i] != '\0'; ++i) {
            if (buffer[used + i] == '\n') {
                used += i;
                found_newline = 1;
                break;
            }
        }

        if (found_newline) {
            break;
        }

        used += i;
    }

    if (!found_newline && used == (size_t)MAX_INPUT_LENGTH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char probe[2];

        if (fgets(probe, sizeof probe, stdin) == NULL) {
            free(buffer);
            return ferror(stdin) ? -1 : 1;
        }

        if (probe[0] != '\n') {
            if (discard_remaining_line(stdin) != 0) {
                free(buffer);
                return -1;
            }
            free(buffer);
            return 1;
        }

        found_newline = 1;
    }

    if (!found_newline && ferror(stdin)) {
        free(buffer);
        return -1;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    size_t length = 0;
    int status;

    status = read_line(&input, &length);
    if (status != 0) {
        if (status > 0) {
            fputs("Input is too long.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (remove_parenthesized(input, length, &output) != 0) {
        fputs("Invalid input or allocation failure.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(output) == EOF) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}