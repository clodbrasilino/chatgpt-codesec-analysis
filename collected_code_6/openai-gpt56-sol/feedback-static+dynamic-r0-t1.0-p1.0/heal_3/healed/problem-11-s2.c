#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int read_line(char **buffer, size_t *capacity, size_t *length)
{
    ssize_t count;

    if (buffer == NULL || capacity == NULL || length == NULL) {
        return -1;
    }

    count = getline(buffer, capacity, stdin);
    if (count < 0) {
        return -1;
    }

    if (count > 0 && (*buffer)[count - 1] == '\n') {
        (*buffer)[--count] = '\0';
    } else if (!feof(stdin)) {
        return -1;
    }

    if (count > 0 && (*buffer)[count - 1] == '\r') {
        (*buffer)[--count] = '\0';
    }

    *length = (size_t)count;
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
    memmove(str + first, str + first + 1, last - first);
    return 2;
}

int main(void)
{
    char *input = NULL;
    char *target_input = NULL;
    size_t input_capacity = 0;
    size_t target_capacity = 0;
    size_t input_length = 0;
    size_t target_length = 0;
    int status = EXIT_FAILURE;

    if (read_line(&input, &input_capacity, &input_length) != 0) {
        goto cleanup;
    }

    if (read_line(&target_input, &target_capacity, &target_length) != 0) {
        goto cleanup;
    }

    if (target_length != 1) {
        goto cleanup;
    }

    if (remove_first_and_last(input, input_length, target_input[0]) < 0) {
        goto cleanup;
    }

    if (fputs(input, stdout) == EOF || fputc('\n', stdout) == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(target_input);
    free(input);
    return status;
}