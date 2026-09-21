#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *find_first_longest_even_word(const char *text)
{
    const char *best_start = NULL;
    size_t best_length = 0;
    const char *current;

    if (text == NULL) {
        return NULL;
    }

    current = text;

    while (*current != '\0') {
        const char *word_start;
        size_t word_length;

        while (*current != '\0' &&
               isspace((unsigned char)*current)) {
            ++current;
        }

        word_start = current;

        while (*current != '\0' &&
               !isspace((unsigned char)*current)) {
            ++current;
        }

        word_length = (size_t)(current - word_start);

        if (word_length > best_length && word_length % 2 == 0) {
            best_start = word_start;
            best_length = word_length;
        }
    }

    if (best_start == NULL || best_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(best_length + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, best_start, best_length);
    result[best_length] = '\0';

    return result;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;

    if (grow_buffer(&buffer, &capacity, 128) != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (character == '\0') {
            free(buffer);
            return -1;
        }

        if (length == SIZE_MAX - 1 ||
            grow_buffer(&buffer, &capacity, length + 2) != 0) {
            free(buffer);
            return -1;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && ferror(stream)) {
        free(buffer);
        return -1;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *word;

    if (read_line(stdin, &input) != 0) {
        fputs("Unable to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    word = find_first_longest_even_word(input);
    free(input);

    if (word == NULL) {
        puts("No even-length word found.");
        return EXIT_SUCCESS;
    }

    puts(word);
    free(word);

    return EXIT_SUCCESS;
}