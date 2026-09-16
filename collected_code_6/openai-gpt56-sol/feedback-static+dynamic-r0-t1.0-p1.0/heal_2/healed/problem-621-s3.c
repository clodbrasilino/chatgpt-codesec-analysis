#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int increment_numeric_string(const char *input, intmax_t k, char **output)
{
    char *end;
    char *result;
    intmax_t value;
    int length;
    size_t size;

    if (input == NULL || output == NULL || *input == '\0') {
        return -1;
    }

    *output = NULL;
    errno = 0;
    value = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0') {
        return -1;
    }

    if ((k > 0 && value > INTMAX_MAX - k) ||
        (k < 0 && value < INTMAX_MIN - k)) {
        return -1;
    }

    value += k;

    length = snprintf(NULL, 0, "%" PRIdMAX, value);
    if (length < 0) {
        return -1;
    }

    size = (size_t)length + 1U;
    if (size == 0U) {
        return -1;
    }

    result = malloc(size);
    if (result == NULL) {
        return -1;
    }

    if (snprintf(result, size, "%" PRIdMAX, value) != length) {
        free(result);
        return -1;
    }

    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    intmax_t k;
    int status = EXIT_SUCCESS;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s k number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    k = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid increment: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    for (int i = 2; i < argc; ++i) {
        char *result = NULL;

        if (increment_numeric_string(argv[i], k, &result) != 0) {
            fprintf(stderr, "Cannot increment: %s\n", argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (puts(result) == EOF) {
            free(result);
            return EXIT_FAILURE;
        }

        free(result);
    }

    return status;
}