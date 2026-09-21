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

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);

            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *character_line = NULL;
    const char *result;
    int status = EXIT_FAILURE;

    if (!read_line(stdin, &input)) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (!read_line(stdin, &character_line) ||
        character_line[0] == '\0' ||
        character_line[1] != '\0') {
        fputs("Failed to read the character.\n", stderr);
        goto cleanup;
    }

    result = find_last_char(input, (unsigned char)character_line[0]);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    status = EXIT_SUCCESS;

cleanup:
    free(character_line);
    free(input);
    return status;
}