#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin++] = string[end];
        string[end--] = temporary;
    }
}

static int left_rotate_string(char *string, size_t length, uintmax_t positions)
{
    size_t offset;

    if (string == NULL && length != 0U) {
        return -1;
    }

    if (length == 0U) {
        return 0;
    }

    offset = (size_t)(positions % length);
    if (offset == 0U) {
        return 0;
    }

    reverse_range(string, 0U, offset - 1U);
    reverse_range(string, offset, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t string_length;
    ssize_t input_length;
    uintmax_t positions;
    char extra;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    string_length = (size_t)input_length;
    if (string_length > 0U && line[string_length - 1U] == '\n') {
        --string_length;
        line[string_length] = '\0';
    }

    if (scanf("%ju%c", &positions, &extra) != 2 || extra != '\n') {
        free(line);
        return EXIT_FAILURE;
    }

    if (left_rotate_string(line, string_length, positions) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (fwrite(line, 1U, string_length, stdout) != string_length ||
        fputc('\n', stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}