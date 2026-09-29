#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int decimal_to_octal(uintmax_t value, char **buffer)
{
    int length;
    char *output;

    if (buffer == NULL) {
        return -1;
    }

    length = snprintf(NULL, 0, "%jo", value);
    if (length < 0 || (size_t)length == SIZE_MAX) {
        return -1;
    }

    output = malloc((size_t)length + 1U);
    if (output == NULL) {
        return -1;
    }

    if (snprintf(output, (size_t)length + 1U, "%jo", value) != length) {
        free(output);
        return -1;
    }

    *buffer = output;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *output = NULL;
    char *end = NULL;
    size_t capacity = 0U;
    ssize_t length;
    uintmax_t value;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        goto cleanup;
    }

    while (length > 0 &&
           (input[(size_t)length - 1U] == '\n' ||
            input[(size_t)length - 1U] == '\r')) {
        input[--length] = '\0';
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || input[0] == '-') {
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