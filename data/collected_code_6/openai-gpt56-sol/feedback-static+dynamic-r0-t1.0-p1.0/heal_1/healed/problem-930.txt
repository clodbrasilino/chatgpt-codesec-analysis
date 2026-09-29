#include <stdio.h>
#include <stdlib.h>
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

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (character == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *new_buffer = realloc(buffer, new_capacity);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return EXIT_FAILURE;
        }

        if (feof(stdin)) {
            return EXIT_SUCCESS;
        }

        fprintf(stderr, "Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    int result = matches_pattern(input);
    free(input);

    if (result < 0) {
        fprintf(stderr, "Regex operation failed.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result ? "Match" : "No match");
    return EXIT_SUCCESS;
}