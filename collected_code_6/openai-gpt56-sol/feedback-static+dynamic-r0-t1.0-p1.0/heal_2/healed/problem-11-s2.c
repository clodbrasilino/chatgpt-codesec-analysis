#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(char *buffer, size_t capacity)
{
    size_t length;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return -1;
    }

    if (fgets(buffer, capacity, stdin) == NULL) {
        return -1;
    }

    length = strlen(buffer);

    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    buffer[0] = '\0';
    return -1;
}

static int remove_first_and_last(char *str, size_t capacity, char target)
{
    char *first;
    char *last;
    size_t length;
    size_t first_offset;
    size_t last_offset;

    if (str == NULL || capacity == 0) {
        return -1;
    }

    length = strnlen(str, capacity);
    if (length == capacity) {
        return -1;
    }

    first = memchr(str, (unsigned char)target, length);
    if (first == NULL) {
        return 0;
    }

    last = first;
    for (char *p = first + 1; p < str + length; ++p) {
        if (*p == target) {
            last = p;
        }
    }

    first_offset = (size_t)(first - str);

    if (first != last) {
        last_offset = (size_t)(last - str);
        memmove(str + last_offset, str + last_offset + 1,
                length - last_offset);
        --length;
    }

    memmove(str + first_offset, str + first_offset + 1,
            length - first_offset);

    return first == last ? 1 : 2;
}

int main(void)
{
    char *input = NULL;
    char *target_input = NULL;
    size_t input_capacity = 0;
    size_t target_capacity = 0;
    ssize_t input_length;
    ssize_t target_length;
    int result = EXIT_FAILURE;

    input_length = getline(&input, &input_capacity, stdin);
    if (input_length < 0) {
        goto cleanup;
    }

    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[--input_length] = '\0';
    } else if (!feof(stdin)) {
        goto cleanup;
    }

    target_length = getline(&target_input, &target_capacity, stdin);
    if (target_length < 0) {
        goto cleanup;
    }

    if (target_length > 0 && target_input[target_length - 1] == '\n') {
        target_input[--target_length] = '\0';
    } else if (!feof(stdin)) {
        goto cleanup;
    }

    if (target_length != 1) {
        goto cleanup;
    }

    if (remove_first_and_last(input, input_capacity, target_input[0]) < 0) {
        goto cleanup;
    }

    if (printf("%s\n", input) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(target_input);
    free(input);
    return result;
}