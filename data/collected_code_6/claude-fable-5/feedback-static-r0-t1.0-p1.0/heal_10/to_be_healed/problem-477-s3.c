#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    char *tmp;
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
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            capacity *= 2;
            tmp = realloc(buffer, capacity);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    if (length >= capacity) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *buffer;
    char *result;

    buffer = read_line(stdin);
    if (buffer == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

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