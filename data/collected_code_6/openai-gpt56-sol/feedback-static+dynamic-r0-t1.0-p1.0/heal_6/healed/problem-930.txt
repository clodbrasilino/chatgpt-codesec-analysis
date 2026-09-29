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

    return result == REG_NOMATCH ? 0 : -1;
}

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        buffer[length++] = (char)character;
    }

    if (length == 0 && feof(stream)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;

    return 1;
}

int main(void)
{
    char *input = NULL;
    int read_result;
    int match_result;

    read_result = read_line(stdin, &input);
    if (read_result < 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_result == 0) {
        return EXIT_SUCCESS;
    }

    match_result = matches_pattern(input);
    free(input);

    if (match_result < 0) {
        fputs("Regex operation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(match_result ? "Match" : "No match");

    return EXIT_SUCCESS;
}