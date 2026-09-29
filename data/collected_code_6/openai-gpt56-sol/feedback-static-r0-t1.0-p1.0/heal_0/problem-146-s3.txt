#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *get_ascii_values(const char *string, size_t *count)
{
    int *values;
    size_t length;

    if (string == NULL || count == NULL) {
        return NULL;
    }

    length = strlen(string);
    *count = length;

    if (length == 0U) {
        return NULL;
    }

    if (length > SIZE_MAX / sizeof(*values)) {
        *count = 0U;
        return NULL;
    }

    values = malloc(length * sizeof(*values));
    if (values == NULL) {
        *count = 0U;
        return NULL;
    }

    for (size_t i = 0U; i < length; ++i) {
        values[i] = (unsigned char)string[i];
    }

    return values;
}

int main(void)
{
    char input[1024];
    int *ascii_values;
    size_t count;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    ascii_values = get_ascii_values(input, &count);
    if (ascii_values == NULL && count != 0U) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        printf("%d%s", ascii_values[i], (i + 1U < count) ? " " : "\n");
    }

    free(ascii_values);
    return EXIT_SUCCESS;
}