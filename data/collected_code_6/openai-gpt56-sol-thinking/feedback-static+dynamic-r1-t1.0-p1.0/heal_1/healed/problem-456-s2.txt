#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int reverse_strings(char *const strings[], const size_t lengths[], size_t count);

int reverse_strings(char *const strings[], const size_t lengths[], size_t count)
{
    size_t i;

    if (count > 0U && (strings == NULL || lengths == NULL)) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        size_t left = 0U;
        size_t right;

        if (strings[i] == NULL) {
            return -1;
        }

        right = lengths[i];

        while (left < right) {
            char temporary;

            --right;
            temporary = strings[i][left];
            strings[i][left] = strings[i][right];
            strings[i][right] = temporary;
            ++left;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    size_t count;
    size_t *lengths = NULL;
    size_t i;
    int status = EXIT_FAILURE;

    if (argc < 1 || argv == NULL) {
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*lengths)) {
        return EXIT_FAILURE;
    }

    if (count > 0U) {
        lengths = malloc(count * sizeof(*lengths));
        if (lengths == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t length = 0U;
        const char *argument = argv[i + 1U];

        if (argument == NULL) {
            goto cleanup;
        }

        while (argument[length] != '\0') {
            ++length;
        }

        lengths[i] = length;
    }

    if (reverse_strings(argv + 1, lengths, count) != 0) {
        (void)fputs("Failed to reverse strings.\n", stderr);
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        if ((lengths[i] > 0U &&
             fwrite(argv[i + 1U], 1U, lengths[i], stdout) != lengths[i]) ||
            fputc('\n', stdout) == EOF) {
            (void)fputs("Failed to write output.\n", stderr);
            goto cleanup;
        }
    }

    if (fflush(stdout) == EOF) {
        (void)fputs("Failed to flush output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(lengths);
    return status;
}