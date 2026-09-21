#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

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

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int current = fgetc(stream);

        if (current == EOF) {
            if (ferror(stream)) {
                free(data);
                return -1;
            }
            break;
        }

        if (current == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2) {
            free(data);
            return -1;
        }

        if (used + 1 >= capacity) {
            size_t required = used + 2;
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;
                if (new_capacity < required) {
                    new_capacity = required;
                }
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

    if (used == 0 && feof(stream)) {
        free(data);
        return 0;
    }

    data[used] = '\0';
    *buffer = data;
    *length = used;

    return 1;
}

static int read_character(FILE *stream, unsigned char *character)
{
    int current;

    if (stream == NULL || character == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    current = fgetc(stream);
    if (current == EOF) {
        return ferror(stream) ? -1 : 0;
    }

    *character = (unsigned char)current;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    const char *result;
    unsigned char target;
    int status;

    status = read_line(stdin, &input, &length);
    if (status == 0) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status < 0) {
        fputs("Failed to read input or allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    status = read_character(stdin, &target);
    if (status <= 0) {
        free(input);
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_last_char(input, target);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    free(input);
    return EXIT_SUCCESS;
}