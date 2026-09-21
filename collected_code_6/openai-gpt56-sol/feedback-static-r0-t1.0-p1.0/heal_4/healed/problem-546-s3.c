#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static const char *find_last_char(const char *str, unsigned char target)
{
    const char *last = NULL;

    if (str == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*str == target) {
            last = str;
        }
    } while (*str++ != '\0');

    return last;
}

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *data;
    size_t used = 0;
    size_t capacity = 128;
    int current;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    while ((current = fgetc(stream)) != EOF && current != '\n') {
        if (used >= SIZE_MAX - 2) {
            free(data);
            return -1;
        }

        if (used + 2 > capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *resized;

            if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = required;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(data, new_capacity);
            if (resized == NULL) {
                free(data);
                return -1;
            }

            data = resized;
            capacity = new_capacity;
        }

        data[used++] = (char)(unsigned char)current;
    }

    if (ferror(stream)) {
        free(data);
        return -1;
    }

    if (current == EOF && used == 0) {
        free(data);
        return 0;
    }

    data[used++] = '\n';
    data[used] = '\0';

    *buffer = data;
    *length = used;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    const char *result;
    int status;
    int ch;

    status = read_line(stdin, &input, &length);
    if (status == 0) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status < 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    ch = fgetc(stdin);
    if (ch == EOF) {
        free(input);
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_last_char(input, (unsigned char)ch);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    free(input);
    return EXIT_SUCCESS;
}