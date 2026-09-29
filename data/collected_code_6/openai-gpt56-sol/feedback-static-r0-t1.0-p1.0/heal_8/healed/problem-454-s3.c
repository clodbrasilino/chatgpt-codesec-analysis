#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
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

    new_capacity = *capacity == 0 ? 64 : *capacity;

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

static int read_word(FILE *stream, char **result)
{
    char *buffer = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    if (stream == NULL || result == NULL) {
        return -1;
    }

    *result = NULL;

    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stream);

            if (next == EOF) {
                if (ferror(stream)) {
                    free(buffer);
                    return -1;
                }
            } else if (next != '\n' && ungetc(next, stream) == EOF) {
                free(buffer);
                return -1;
            }

            break;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (grow_buffer(&buffer, &capacity, length + 2) != 0) {
            free(buffer);
            return -1;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ch == EOF) {
        if (ferror(stream)) {
            free(buffer);
            return -1;
        }

        if (length == 0) {
            free(buffer);
            return 0;
        }
    }

    if (length == SIZE_MAX ||
        grow_buffer(&buffer, &capacity, length + 1) != 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *result = buffer;
    return 1;
}

int main(void)
{
    char *word = NULL;
    int status = read_word(stdin, &word);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 0) {
        return EXIT_SUCCESS;
    }

    if (puts(contains_z(word) ? "Match" : "No match") == EOF) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}