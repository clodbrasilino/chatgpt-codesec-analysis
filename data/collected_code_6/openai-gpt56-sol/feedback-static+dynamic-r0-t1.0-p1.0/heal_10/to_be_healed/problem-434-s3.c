#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches(const char *str)
{
    if (str == NULL || str[0] != 'a' || str[1] != 'b') {
        return false;
    }

    str += 2;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;

    *line = malloc(capacity);
    if (*line == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity > SIZE_MAX / 2) {
                free(*line);
                *line = NULL;
                return -1;
            }

            new_capacity = capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                free(*line);
                *line = NULL;
                return -1;
            }

            *line = new_line;
            capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(*line);
        *line = NULL;
        return -1;
    }

    if (ch == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            ungetc(next, stdin);
        }

        if (ferror(stdin)) {
            free(*line);
            *line = NULL;
            return -1;
        }
    }

    if (ch == EOF && length == 0) {
        free(*line);
        *line = NULL;
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

int main(void)
{
    char *input = NULL;
    int status = read_line(&input);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    int output_status = puts(matches(input) ? "Match" : "No match");
    free(input);

    return output_status == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}