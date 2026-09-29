#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void remove_chars(char *str, const char *mask);
static bool read_line(char *buffer, size_t size);

void remove_chars(char *str, const char *mask)
{
    bool present[256] = { false };
    size_t i;
    size_t j;

    if (str == NULL || mask == NULL) {
        return;
    }

    for (i = 0; mask[i] != '\0'; i++) {
        present[(unsigned char)mask[i]] = true;
    }

    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (!present[(unsigned char)str[i]]) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

static bool read_line(char *buffer, size_t size)
{
    char *newline;

    if (buffer == NULL || size == 0) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1] = '\0';

    newline = memchr(buffer, '\n', size);
    if (newline != NULL) {
        *newline = '\0';
    } else {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    }

    return true;
}

int main(void)
{
    char *first;
    char *second;

    first = calloc(BUFFER_SIZE, sizeof(char));
    if (first == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    second = calloc(BUFFER_SIZE, sizeof(char));
    if (second == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first);
        return EXIT_FAILURE;
    }

    printf("Enter the first string: ");
    if (!read_line(first, BUFFER_SIZE)) {
        fprintf(stderr, "Error reading first string\n");
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    printf("Enter the second string: ");
    if (!read_line(second, BUFFER_SIZE)) {
        fprintf(stderr, "Error reading second string\n");
        free(first);
        free(second);
        return EXIT_FAILURE;
    }

    remove_chars(first, second);

    printf("Result: %s\n", first);

    free(first);
    free(second);

    return EXIT_SUCCESS;
}