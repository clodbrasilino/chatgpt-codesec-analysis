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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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