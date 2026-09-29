#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ASCII_RANGE 256
#define INITIAL_CAPACITY 64

char find_max_occurring_char(const char *str)
{
    int counts[ASCII_RANGE] = {0};
    size_t i;
    char max_char;
    int max_count;

    if (str == NULL || str[0] == '\0') {
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        counts[(unsigned char)str[i]]++;
    }

    max_char = str[0];
    max_count = counts[(unsigned char)str[0]];

    for (i = 1; str[i] != '\0'; i++) {
        if (counts[(unsigned char)str[i]] > max_count) {
            max_count = counts[(unsigned char)str[i]];
            max_char = str[i];
        }
    }

    return max_char;
}

static char *read_line(FILE *stream)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int c;

    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            new_capacity = capacity * 2;

            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length++] = (char)c;
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (c == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *buffer;
    char result;

    printf("Enter a string: ");
    fflush(stdout);

    buffer = read_line(stdin);

    if (buffer == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty string provided\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    result = find_max_occurring_char(buffer);

    if (result == '\0') {
        fprintf(stderr, "Could not determine maximum occurring character\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Maximum occurring character: '%c'\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}