#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temporary = *start;
        *start++ = *end;
        *end-- = temporary;
    }
}

static int left_rotate(char *string, size_t length, size_t positions)
{
    if (string == NULL) {
        return -1;
    }

    if (length == 0) {
        return 0;
    }

    positions %= length;

    if (positions == 0) {
        return 0;
    }

    reverse_range(string, string + positions - 1);
    reverse_range(string + positions, string + length - 1);
    reverse_range(string, string + length - 1);

    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0 || required <= *capacity) {
        return -1;
    }

    new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required || new_capacity <= *capacity) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(FILE *stream, char **line, size_t *length)
{
    const size_t initial_capacity = 128;
    size_t capacity = initial_capacity;
    size_t used = 0;
    char *buffer;

    if (stream == NULL || line == NULL || length == NULL) {
        return -1;
    }

    *line = NULL;
    *length = 0;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character;

        if (used > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        if (capacity - used < 2) {
            if (grow_buffer(&buffer, &capacity, used + 2) != 0) {
                free(buffer);
                return -1;
            }
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stream);

        if (character == '\n') {
            break;
        }

        if (character == EOF) {
            if (ferror(stream) || used == 0) {
                free(buffer);
                return -1;
            }

            break;
        }

        buffer[used] = (char)(unsigned char)character;
        ++used;
    }

    buffer[used] = '\0';
    *line = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *string = NULL;
    char *input = NULL;
    char *end = NULL;
    size_t string_length = 0;
    size_t input_length = 0;
    size_t positions = 0;
    unsigned long long value;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &string, &string_length) != 0) {
        fputs("Failed to read the string.\n", stderr);
        goto cleanup;
    }

    if (read_line(stdin, &input, &input_length) != 0) {
        fputs("Failed to read the rotation count.\n", stderr);
        goto cleanup;
    }

    if (input_length == 0) {
        fputs("Invalid rotation count.\n", stderr);
        goto cleanup;
    }

    if (input[0] == '-') {
        fputs("Rotation count must be nonnegative.\n", stderr);
        goto cleanup;
    }

    errno = 0;
    value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0') {
        fputs("Invalid rotation count.\n", stderr);
        goto cleanup;
    }

    if (string_length != 0) {
#if SIZE_MAX > ULLONG_MAX
        if (string_length > (size_t)ULLONG_MAX) {
            positions = (size_t)value;
        } else {
            positions = (size_t)(value %
                (unsigned long long)string_length);
        }
#else
        positions = (size_t)(value %
            (unsigned long long)string_length);
#endif
    }

    if (left_rotate(string, string_length, positions) != 0) {
        fputs("Failed to rotate the string.\n", stderr);
        goto cleanup;
    }

    if (fwrite(string, 1, string_length, stdout) != string_length ||
        fputc('\n', stdout) == EOF) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    free(string);
    return status;
}