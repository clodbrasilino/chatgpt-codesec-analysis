#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1024U

static int replace_spaces(char *string, size_t length, char replacement)
{
    size_t i;

    if (string == NULL || replacement == '\0') {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        if (string[i] == ' ') {
            string[i] = replacement;
        }
    }

    return 0;
}

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    }

    return 0;
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    size_t used;
    int ch;

    if (buffer == NULL || length == NULL ||
        capacity < 2U || capacity > (size_t)INT_MAX) {
        return -1;
    }

    buffer[0] = '\0';
    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return -1;
    }

    for (used = 0U; used < capacity && buffer[used] != '\0'; ++used) {
        if (buffer[used] == '\n') {
            buffer[used] = '\0';
            *length = used;
            return 0;
        }
    }

    if (used >= capacity) {
        buffer[0] = '\0';
        return -1;
    }

    if (used < capacity - 1U) {
        *length = used;
        return 0;
    }

    ch = getchar();

    if (ch == '\n') {
        *length = used;
        return 0;
    }

    if (ch == EOF) {
        if (ferror(stdin)) {
            buffer[0] = '\0';
            return -1;
        }

        *length = used;
        return 0;
    }

    if (discard_line() != 0) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[0] = '\0';
    return -1;
}

static int read_replacement(char *replacement)
{
    int ch;
    int terminator;

    if (replacement == NULL) {
        return -1;
    }

    ch = getchar();
    if (ch == EOF || ch == '\0' || ch == '\n') {
        return -1;
    }

    terminator = getchar();

    if (terminator == '\n') {
        *replacement = (char)ch;
        return 0;
    }

    if (terminator == EOF) {
        if (ferror(stdin)) {
            return -1;
        }

        *replacement = (char)ch;
        return 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    return -1;
}

int main(void)
{
    char *input;
    char replacement;
    size_t length;
    int status;

    input = malloc(INPUT_SIZE);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    status = EXIT_FAILURE;

    if (read_line(input, INPUT_SIZE, &length) != 0) {
        goto cleanup;
    }

    if (read_replacement(&replacement) != 0) {
        goto cleanup;
    }

    if (replace_spaces(input, length, replacement) != 0) {
        goto cleanup;
    }

    if (fwrite(input, sizeof(*input), length, stdout) != length) {
        goto cleanup;
    }

    if (putchar('\n') == EOF) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}