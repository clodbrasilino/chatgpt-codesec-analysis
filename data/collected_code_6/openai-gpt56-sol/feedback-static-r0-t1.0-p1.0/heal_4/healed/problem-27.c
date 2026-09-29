#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    if (string == NULL) {
        return;
    }

    char *read_ptr = string;
    char *write_ptr = string;

    while (*read_ptr != '\0') {
        unsigned char character = (unsigned char)*read_ptr++;

        if (!isdigit(character)) {
            *write_ptr++ = (char)character;
        }
    }

    *write_ptr = '\0';
}

static void remove_digits_from_list(char *const strings[], size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        remove_digits(strings[i]);
    }
}

static void free_strings(char **strings, size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static char *duplicate_string(const char *source, size_t max_length)
{
    if (source == NULL) {
        errno = EINVAL;
        return NULL;
    }

    const char *terminator = memchr(source, '\0', max_length);

    if (terminator == NULL) {
        errno = EOVERFLOW;
        return NULL;
    }

    size_t length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1U) {
        errno = EOVERFLOW;
        return NULL;
    }

    size_t allocation_size = length + 1U;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return NULL;
    }

    if (snprintf(copy, allocation_size, "%s", source) < 0) {
        free(copy);
        errno = EIO;
        return NULL;
    }

    return copy;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argv == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s string [string ...]\n", program);
        return EXIT_FAILURE;
    }

    const size_t max_argument_length = 1024U * 1024U;
    const size_t count = (size_t)argc - 1U;

    if (count > SIZE_MAX / sizeof(char *)) {
        fputs("Too many input strings\n", stderr);
        return EXIT_FAILURE;
    }

    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        strings[i] = duplicate_string(argv[i + 1U], max_argument_length);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed or input is too long\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }
    }

    remove_digits_from_list(strings, count);

    for (size_t i = 0; i < count; ++i) {
        if (puts(strings[i]) == EOF) {
            fputs("Output error\n", stderr);
            free_strings(strings, count);
            return EXIT_FAILURE;
        }
    }

    free_strings(strings, count);
    return EXIT_SUCCESS;
}