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

    new_capacity = (*capacity == 0U) ? 128U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
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

static int read_line(FILE *stream, char **buffer, size_t *length)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t used = 0U;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (stream == NULL || buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0U;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) != 0 || used == 0U) {
                free(line);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (used > SIZE_MAX - 2U) {
            free(line);
            return -1;
        }

        if (ensure_capacity(&line, &capacity, used + 2U) != 0) {
            free(line);
            return -1;
        }

        line[used] = (char)ch;
        ++used;
    }

    if (used == SIZE_MAX ||
        ensure_capacity(&line, &capacity, used + 1U) != 0) {
        free(line);
        return -1;
    }

    line[used] = '\0';
    *buffer = line;
    *length = used;
    return 0;
}

static int remove_first_and_last(char *str, size_t *length, char target)
{
    size_t first;
    size_t last;
    size_t i;

    if (str == NULL || length == NULL) {
        return -1;
    }

    first = *length;
    last = *length;

    for (i = 0U; i < *length; ++i) {
        if (str[i] == target) {
            if (first == *length) {
                first = i;
            }
            last = i;
        }
    }

    if (first == *length) {
        return 0;
    }

    if (first == last) {
        memmove(str + first, str + first + 1U, *length - first);
        --*length;
        return 1;
    }

    memmove(str + last, str + last + 1U, *length - last);
    --*length;

    memmove(str + first, str + first + 1U, *length - first);
    --*length;

    return 2;
}

int main(void)
{
    char *input = NULL;
    char *target_line = NULL;
    size_t input_length = 0U;
    size_t target_length = 0U;
    int result = EXIT_FAILURE;

    if (read_line(stdin, &input, &input_length) != 0) {
        goto cleanup;
    }

    if (read_line(stdin, &target_line, &target_length) != 0 ||
        target_length != 1U) {
        goto cleanup;
    }

    if (remove_first_and_last(input, &input_length, target_line[0]) < 0) {
        goto cleanup;
    }

    if (input_length != 0U &&
        fwrite(input, 1U, input_length, stdout) != input_length) {
        goto cleanup;
    }

    if (fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(target_line);
    free(input);
    return result;
}