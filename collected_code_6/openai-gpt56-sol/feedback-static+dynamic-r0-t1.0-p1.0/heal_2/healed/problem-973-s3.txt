#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void reverse_range(char *string, size_t begin, size_t end)
{
    while (begin < end) {
        char temporary = string[begin];
        string[begin] = string[end];
        string[end] = temporary;
        ++begin;
        --end;
    }
}

static int left_rotate_string(char *string, size_t length,
                              unsigned long long positions)
{
    size_t rotation;

    if (string == NULL) {
        return -1;
    }

    if (length == 0U) {
        return 0;
    }

    rotation = (size_t)(positions % (unsigned long long)length);

    if (rotation == 0U) {
        return 0;
    }

    reverse_range(string, 0U, rotation - 1U);
    reverse_range(string, rotation, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

static int parse_positions(const char *input, unsigned long long *positions)
{
    char *end;
    unsigned long long value;

    if (input == NULL || positions == NULL) {
        return -1;
    }

    while (*input == ' ' || *input == '\t' || *input == '\r') {
        ++input;
    }

    if (*input == '\0' || *input == '\n' || *input == '-') {
        return -1;
    }

    errno = 0;
    value = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *positions = value;
    return 0;
}

int main(void)
{
    char *line = NULL;
    char *positions_line = NULL;
    size_t line_capacity = 0U;
    size_t positions_capacity = 0U;
    size_t string_length;
    ssize_t input_length;
    unsigned long long positions;
    int result = EXIT_FAILURE;

    input_length = getline(&line, &line_capacity, stdin);
    if (input_length < 0) {
        goto cleanup;
    }

    string_length = (size_t)input_length;

    if (string_length > 0U && line[string_length - 1U] == '\n') {
        line[--string_length] = '\0';

        if (string_length > 0U && line[string_length - 1U] == '\r') {
            line[--string_length] = '\0';
        }
    }

    input_length = getline(&positions_line, &positions_capacity, stdin);
    if (input_length < 0) {
        goto cleanup;
    }

    if (parse_positions(positions_line, &positions) != 0) {
        goto cleanup;
    }

    if (left_rotate_string(line, string_length, positions) != 0) {
        goto cleanup;
    }

    if (puts(line) == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(positions_line);
    free(line);
    return result;
}