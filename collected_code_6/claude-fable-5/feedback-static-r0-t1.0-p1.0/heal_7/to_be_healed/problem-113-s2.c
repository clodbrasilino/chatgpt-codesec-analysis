#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 1048576

int is_integer(const char *str)
{
    char *endptr;
    long value;

    if (str == NULL) {
        return 0;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return 0;
    }

    errno = 0;
    value = strtol(str, &endptr, 10);

    if (errno == ERANGE) {
        return 0;
    }

    if (endptr == str) {
        return 0;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 0;
    }

    (void)value;
    return 1;
}

char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *line;
    int ch;

    if (stream == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length >= MAX_LINE_LENGTH) {
            free(line);
            return NULL;
        }
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *tmp;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }
            new_capacity = capacity * 2;
            tmp = realloc(line, new_capacity);
            if (tmp == NULL) {
                free(line);
                return NULL;
            }
            line = tmp;
            capacity = new_capacity;
        }
        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return NULL;
    }

    line[length] = '\0';
    return line;
}

int main(void)
{
    char *buffer;

    printf("Enter a string: ");
    fflush(stdout);

    buffer = read_line(stdin);
    if (buffer == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (is_integer(buffer)) {
        printf("\"%s\" is a valid integer\n", buffer);
    } else {
        printf("\"%s\" is not a valid integer\n", buffer);
    }

    free(buffer);
    return EXIT_SUCCESS;
}