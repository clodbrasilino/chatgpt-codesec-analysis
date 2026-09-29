#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static int ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity == 0 ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return -1;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 0;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 0;
    int ch;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (*length == SIZE_MAX - 1 ||
            ensure_capacity(buffer, &capacity, *length + 2) != 0) {
            free(*buffer);
            *buffer = NULL;
            return -1;
        }

        (*buffer)[(*length)++] = (char)ch;
    }

    if (ch == EOF && *length == 0) {
        free(*buffer);
        *buffer = NULL;
        return -1;
    }

    if (ensure_capacity(buffer, &capacity, *length + 1) != 0) {
        free(*buffer);
        *buffer = NULL;
        return -1;
    }

    (*buffer)[*length] = '\0';
    return 0;
}

static int remove_first_and_last(char *str, size_t length, char target)
{
    size_t first = length;
    size_t last = length;

    if (str == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == target) {
            if (first == length) {
                first = i;
            }
            last = i;
        }
    }

    if (first == length) {
        return 0;
    }

    if (first == last) {
        memmove(str + first, str + first + 1, length - first);
        return 1;
    }

    memmove(str + last, str + last + 1, length - last);
    memmove(str + first, str + first + 1, length - first - 1);
    return 2;
}

int main(void)
{
    char *input = NULL;
    char *target_line = NULL;
    size_t input_length = 0;
    size_t target_length = 0;
    int result = EXIT_FAILURE;

    if (read_line(&input, &input_length) != 0) {
        goto cleanup;
    }

    if (read_line(&target_line, &target_length) != 0 ||
        target_length != 1) {
        goto cleanup;
    }

    if (remove_first_and_last(input, input_length, target_line[0]) < 0) {
        goto cleanup;
    }

    if (printf("%s\n", input) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(target_line);
    free(input);
    return result;
}