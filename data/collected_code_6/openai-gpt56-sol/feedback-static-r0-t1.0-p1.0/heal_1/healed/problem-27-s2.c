#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_digits(char *string)
{
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
        if (strings[i] != NULL) {
            remove_digits(strings[i]);
        }
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

static char *duplicate_string(const char *source)
{
    if (source == NULL) {
        return NULL;
    }

    size_t length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    char *destination = malloc(length + 1);
    if (destination == NULL) {
        return NULL;
    }

    snprintf(destination, length + 1, "%s", source);
    return destination;
}

int main(void)
{
    static const char *const inputs[] = {
        "abc123",
        "2026 edition",
        "no digits",
        "1a2b3c"
    };

    const size_t count = sizeof(inputs) / sizeof(inputs[0]);
    char **strings = calloc(count, sizeof(*strings));

    if (strings == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        strings[i] = duplicate_string(inputs[i]);

        if (strings[i] == NULL) {
            fputs("Memory allocation failed\n", stderr);
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