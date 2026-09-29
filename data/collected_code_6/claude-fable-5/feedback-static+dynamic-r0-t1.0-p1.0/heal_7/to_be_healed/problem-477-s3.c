#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define BUFFER_SIZE 256

char *to_lower_case(char *str)
{
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }

    return str;
}

int main(void)
{
    char *buffer;
    char *result;
    size_t capacity = BUFFER_SIZE;
    size_t length = 0;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > SIZE_MAX / 2) {
                fprintf(stderr, "Input too large\n");
                free(buffer);
                return EXIT_FAILURE;
            }
            new_capacity = capacity * 2;
            tmp = realloc(buffer, new_capacity);
            if (tmp == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(buffer);
                return EXIT_FAILURE;
            }
            buffer = tmp;
            capacity = new_capacity;
        }
        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (length == 0 && ch == EOF) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[length] = '\0';

    result = to_lower_case(buffer);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}