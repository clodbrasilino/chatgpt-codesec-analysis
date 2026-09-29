#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_byte(FILE *stream, unsigned char *value)
{
    size_t count;

    if (stream == NULL || value == NULL) {
        return -1;
    }

    count = fread(value, 1, 1, stream);
    if (count == 1) {
        return 1;
    }

    return ferror(stream) ? -1 : 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = SIZE_MAX;
        } else {
            new_capacity *= 2;
        }

        if (new_capacity < required) {
            return -1;
        }
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_token(FILE *stream, char **output)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;
    unsigned char byte;
    int status;

    if (stream == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    do {
        status = read_byte(stream, &byte);
        if (status <= 0) {
            return status;
        }
    } while (isspace(byte));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        size_t required;

        if (byte == '\0') {
            free(buffer);
            return -1;
        }

        if (length > SIZE_MAX - 2) {
            free(buffer);
            return -1;
        }

        required = length + 2;
        if (grow_buffer(&buffer, &capacity, required) != 0) {
            free(buffer);
            return -1;
        }

        buffer[length++] = (char)byte;

        status = read_byte(stream, &byte);
        if (status < 0) {
            free(buffer);
            return -1;
        }

        if (status == 0 || isspace(byte)) {
            break;
        }
    }

    buffer[length] = '\0';
    *output = buffer;
    return 1;
}

static int is_binary_string(const char *string)
{
    size_t index;

    if (string == NULL || string[0] == '\0') {
        return 0;
    }

    for (index = 0; string[index] != '\0'; ++index) {
        if (string[index] != '0' && string[index] != '1') {
            return 0;
        }
    }

    return 1;
}

static int minimum_swaps(const char *source,
                         const char *target,
                         size_t *result)
{
    size_t index = 0;
    size_t zero_to_one = 0;
    size_t one_to_zero = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    if (!is_binary_string(source) || !is_binary_string(target)) {
        return -1;
    }

    while (source[index] != '\0' && target[index] != '\0') {
        if (source[index] == '0' && target[index] == '1') {
            ++zero_to_one;
        } else if (source[index] == '1' && target[index] == '0') {
            ++one_to_zero;
        }

        ++index;
    }

    if (source[index] != '\0' || target[index] != '\0') {
        return 1;
    }

    if (zero_to_one != one_to_zero) {
        return 1;
    }

    *result = zero_to_one;
    return 0;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t swaps = 0;
    int status;
    int exit_status = EXIT_FAILURE;

    status = read_token(stdin, &source);
    if (status != 1) {
        fprintf(stderr, "Failed to read the first binary string.\n");
        goto cleanup;
    }

    status = read_token(stdin, &target);
    if (status != 1) {
        fprintf(stderr, "Failed to read the second binary string.\n");
        goto cleanup;
    }

    status = minimum_swaps(source, target, &swaps);
    if (status < 0) {
        fprintf(stderr, "Invalid binary string.\n");
        goto cleanup;
    }

    if (status > 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(target);
    free(source);
    return exit_status;
}