#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <ctype.h>

static int decimal_to_octal(uintmax_t value, char *buffer, size_t size)
{
    int result;

    if (buffer == NULL || size == 0U) {
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
    size_t capacity = 0U;
    ssize_t length;
    char output[(sizeof(uintmax_t) * 8U + 2U) / 3U + 1U];
    char *end = NULL;
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