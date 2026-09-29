#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_SIZE 1024

size_t longest_word_length(const char *str)
{
    size_t max_len = 0;
    size_t current_len = 0;
    size_t i = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[i] != '\0') {
        if (isspace((unsigned char)str[i])) {
            if (current_len > max_len) {
                max_len = current_len;
            }
            current_len = 0;
        } else {
            current_len++;
        }
        i++;
    }

    if (current_len > max_len) {
        max_len = current_len;
    }

    return max_len;
}

static char *read_line(FILE *stream)
{
    size_t capacity = INITIAL_SIZE;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            char *new_buffer;
            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            new_buffer = realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)ch;
    }

    if (length == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *buffer;
    size_t result;

    if (printf("Enter a sentence: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    buffer = read_line(stdin);
    if (buffer == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    result = longest_word_length(buffer);
    free(buffer);

    if (printf("Length of the longest word: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}