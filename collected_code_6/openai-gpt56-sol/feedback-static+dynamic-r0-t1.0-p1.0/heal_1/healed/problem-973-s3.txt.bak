#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

static int left_rotate_string(char *string, unsigned long long positions)
{
    size_t length;
    size_t rotation;

    if (string == NULL) {
        return -1;
    }

    length = strlen(string);
    if (length == 0U) {
        return 0;
    }

    if (length <= ULLONG_MAX) {
        rotation = (size_t)(positions % (unsigned long long)length);
    } else {
        rotation = (size_t)positions;
    }

    if (rotation == 0U) {
        return 0;
    }

    reverse_range(string, 0U, rotation - 1U);
    reverse_range(string, rotation, length - 1U);
    reverse_range(string, 0U, length - 1U);

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t input_length;
    unsigned long long positions;
    int trailing;

    input_length = getline(&line, &capacity, stdin);
    if (input_length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (input_length > 0 && line[input_length - 1] == '\n') {
        line[input_length - 1] = '\0';
    }

    if (scanf("%llu", &positions) != 1) {
        free(line);
        return EXIT_FAILURE;
    }

    trailing = getchar();
    if (trailing == '\r') {
        trailing = getchar();
    }

    if (trailing != '\n' && trailing != EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    if (left_rotate_string(line, positions) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (puts(line) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}