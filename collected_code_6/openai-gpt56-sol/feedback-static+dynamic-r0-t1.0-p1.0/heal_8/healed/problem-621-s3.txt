#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int increment_numeric_string(const char *input, intmax_t increment,
                                    char **output)
{
    char *end;
    char *result;
    intmax_t value;
    int length;
    int written;
    size_t size;
    static const char format[] = "%" PRIdMAX;

    if (input == NULL || output == NULL || input[0] == '\0') {
        return -1;
    }

    *output = NULL;
    errno = 0;
    value = strtoimax(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0') {
        return -1;
    }

    if ((increment > 0 && value > INTMAX_MAX - increment) ||
        (increment < 0 && value < INTMAX_MIN - increment)) {
        return -1;
    }

    value += increment;

    length = snprintf(NULL, 0, format, value);
    if (length < 0 || (size_t)length == SIZE_MAX) {
        return -1;
    }

    size = (size_t)length + 1;
    result = malloc(size);
    if (result == NULL) {
        return -1;
    }

    written = snprintf(result, size, format, value);
    if (written != length || written < 0 || (size_t)written >= size) {
        free(result);
        return -1;
    }

    *output = result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    intmax_t increment;
    int status = EXIT_SUCCESS;

    if (argc < 3) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        (void)fprintf(stderr, "Usage: %s k number [number ...]\n", program);
        return EXIT_FAILURE;
    }

    errno = 0;
    increment = strtoimax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        (void)fprintf(stderr, "Invalid increment: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    for (int i = 2; i < argc; ++i) {
        char *result = NULL;

        if (increment_numeric_string(argv[i], increment, &result) != 0) {
            (void)fprintf(stderr, "Cannot increment: %s\n", argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (fprintf(stdout, "%s\n", result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }

        free(result);
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return status;
}