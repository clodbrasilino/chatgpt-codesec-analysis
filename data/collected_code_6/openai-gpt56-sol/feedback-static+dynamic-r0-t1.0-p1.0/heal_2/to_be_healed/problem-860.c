#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int ends_with_alphanumeric(const char *string, bool *result)
{
    regex_t regex;
    int status;

    if (string == NULL || result == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:alnum:]]+$", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (status == 0) {
        *result = true;
        return 0;
    }

    if (status == REG_NOMATCH) {
        *result = false;
        return 0;
    }

    return -1;
}

static char *read_line(FILE *stream)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 128;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
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

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    bool result;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ends_with_alphanumeric(input, &result) != 0) {
        fputs("Regex operation failed.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    puts(result ? "true" : "false");
    free(input);
    return EXIT_SUCCESS;
}