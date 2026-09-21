#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           memcmp(string, "abbb", length) == 0;
}

static int read_line(char **line, size_t *length)
{
    size_t capacity = 16U;
    size_t used = 0U;
    char *buffer;
    int character;

    if (line == NULL || length == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (used + 1U >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)character;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                free(buffer);
                return -1;
            }
        }
    }

    if (ferror(stdin)) {
        free(buffer);
        return -1;
    }

    if (character == EOF && used == 0U) {
        free(buffer);
        return 0;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    int result = read_line(&input, &length);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("No match");
        return EXIT_SUCCESS;
    }

    puts(matches_pattern(input, length) ? "Match" : "No match");
    free(input);

    return EXIT_SUCCESS;
}