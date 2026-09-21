#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
    if (string == NULL) {
        return;
    }

    unsigned char *source = (unsigned char *)string;
    char *destination = string;

    while (*source != '\0') {
        if (!isdigit(*source)) {
            *destination++ = (char)*source;
        }
        ++source;
    }

    *destination = '\0';
}

static void remove_digits_from_list(char *strings[], size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        remove_digits(strings[i]);
    }
}

static void free_strings(char *strings[], size_t count)
{
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static char *duplicate_string(const char *source, size_t source_size)
{
    if (source == NULL || source_size == 0) {
        return NULL;
    }

    const char *terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return NULL;
    }

    size_t length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    size_t destination_size = length + 1;
    char *destination = malloc(destination_size);
    if (destination == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(destination, source, length);
    }

    destination[length] = '\0';
    return destination;
}

int main(void)
{
    static const char inputs[][32] = {
        "abc123",
        "2026 edition",
        "no digits",
        "1a2b3c"
    };

    const size_t count = sizeof(inputs) / sizeof(inputs[0]);

    if (count > SIZE_MAX / sizeof(char *)) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    char **strings = calloc(count, sizeof(*strings));
    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        strings[i] = duplicate_string(inputs[i], sizeof(inputs[i]));
        if (strings[i] == NULL) {
            fputs("String duplication failed\n", stderr);
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