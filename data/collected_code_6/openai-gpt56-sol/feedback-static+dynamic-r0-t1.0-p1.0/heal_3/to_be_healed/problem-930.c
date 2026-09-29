#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <regex.h>

static int matches_pattern(const char *string)
{
    regex_t regex;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, "^ab*$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return 1;
    }

    if (result == REG_NOMATCH) {
        return 0;
    }

    return -1;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == EOF || character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2;
                }
            }

            if (new_capacity <= length + 1) {
                free(buffer);
                return -1;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    if (capacity <= length) {
        char *new_buffer = realloc(buffer, length + 1);
        if (new_buffer == NULL) {
            free(buffer);
            return -1;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    int read_result = read_line(stdin, &input);

    if (read_result < 0) {
        fprintf(stderr, "Failed to read input or allocate memory.\n");
        return EXIT_FAILURE;
    }

    if (read_result == 0) {
        return EXIT_SUCCESS;
    }

    int match_result = matches_pattern(input);
    free(input);

    if (match_result < 0) {
        fprintf(stderr, "Regex operation failed.\n");
        return EXIT_FAILURE;
    }

    puts(match_result ? "Match" : "No match");
    return EXIT_SUCCESS;
}