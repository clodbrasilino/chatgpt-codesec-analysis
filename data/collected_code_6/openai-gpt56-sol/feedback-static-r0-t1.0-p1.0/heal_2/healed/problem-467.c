#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <ctype.h>

#define OCTAL_BUFFER_SIZE ((sizeof(uintmax_t) * 8U + 2U) / 3U + 1U)

static int decimal_to_octal(uintmax_t value, char *buffer, size_t size)
{
    int result;

    if (buffer == NULL || size < OCTAL_BUFFER_SIZE) {
        return -1;
    }

    result = snprintf(buffer, size, "%jo", value);
    if (result < 0 || (size_t)result >= size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char output[OCTAL_BUFFER_SIZE];
    char *start;
    char *end;
    uintmax_t value;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (!feof(stdin)) {
        goto cleanup;
    }

    start = input;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
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

    if (decimal_to_octal(value, output, sizeof(output)) != 0) {
        goto cleanup;
    }

    if (printf("%s\n", output) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}