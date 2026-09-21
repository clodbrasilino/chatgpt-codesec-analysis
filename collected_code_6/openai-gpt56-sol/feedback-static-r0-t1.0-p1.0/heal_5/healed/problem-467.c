#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int decimal_to_octal(uintmax_t value, char **output)
{
    int length;
    char *buffer;

    if (output == NULL) {
        return -1;
    }

    *output = NULL;

    length = snprintf(NULL, 0, "%jo", value);
    if (length < 0) {
        return -1;
    }

    buffer = malloc((size_t)length + 1U);
    if (buffer == NULL) {
        return -1;
    }

    if (snprintf(buffer, (size_t)length + 1U, "%jo", value) != length) {
        free(buffer);
        return -1;
    }

    *output = buffer;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    char *start;
    char *end;
    size_t capacity = 0;
    ssize_t length;
    uintmax_t value;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        goto cleanup;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start) {
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    if (decimal_to_octal(value, &output) != 0) {
        goto cleanup;
    }

    if (printf("%s\n", output) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(output);
    free(input);
    return status;
}