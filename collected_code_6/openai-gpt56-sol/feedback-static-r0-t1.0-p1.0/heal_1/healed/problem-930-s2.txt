#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int matches_pattern(const char *string, bool *matches)
{
    static const char pattern[] = "^ab*$";
    regex_t regex;
    int result;

    if (string == NULL || matches == NULL) {
        return REG_INVARG;
    }

    *matches = false;

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return result;
    }

    result = regexec(&regex, string, 0, NULL, 0);
    if (result == 0) {
        *matches = true;
        result = 0;
    } else if (result == REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_buffer;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length + 1 > capacity) {
        char *new_buffer = realloc(buffer, length + 1);

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
    char *input;
    bool matches;
    int result;

    input = read_line(stdin);
    if (input == NULL) {
        if (ferror(stdin)) {
            perror("Input error");
        } else if (feof(stdin)) {
            fputs("No input provided\n", stderr);
        } else {
            fputs("Unable to allocate input buffer\n", stderr);
        }
        return EXIT_FAILURE;
    }

    result = matches_pattern(input, &matches);
    free(input);

    if (result != 0) {
        size_t size = regerror(result, NULL, NULL, 0);
        char *message = malloc(size);

        if (message != NULL) {
            regerror(result, NULL, message, size);
            fprintf(stderr, "Regex error: %s\n", message);
            free(message);
        } else {
            fputs("Regex error\n", stderr);
        }

        return EXIT_FAILURE;
    }

    puts(matches ? "Match" : "No match");
    return EXIT_SUCCESS;
}