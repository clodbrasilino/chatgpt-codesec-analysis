#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_string(char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    while (left < right) {
        char temporary;

        --right;
        temporary = string[left];
        string[left] = string[right];
        string[right] = temporary;
        ++left;
    }
}

static int reverse_strings(char *strings[], const size_t lengths[], size_t count)
{
    if (count != 0U && (strings == NULL || lengths == NULL)) {
        return -1;
    }

    for (size_t index = 0; index < count; ++index) {
        if (strings[index] == NULL) {
            return -1;
        }

        reverse_string(strings[index], lengths[index]);
    }

    return 0;
}

int main(void)
{
    static const char *const source_strings[] = {
        "Hello",
        "World",
        "Secure C"
    };
    const size_t lengths[] = {
        sizeof("Hello") - 1U,
        sizeof("World") - 1U,
        sizeof("Secure C") - 1U
    };
    const size_t count = sizeof(source_strings) / sizeof(source_strings[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *strings[sizeof(source_strings) / sizeof(source_strings[0])] = { NULL };

    for (size_t index = 0; index < count; ++index) {
        if (lengths[index] == SIZE_MAX) {
            goto failure;
        }

        strings[index] = malloc(lengths[index] + 1U);
        if (strings[index] == NULL) {
            goto failure;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[index], source_strings[index], lengths[index]);
        strings[index][lengths[index]] = '\0';
    }

    if (reverse_strings(strings, lengths, count) != 0) {
        goto failure;
    }

    for (size_t index = 0; index < count; ++index) {
        if (puts(strings[index]) == EOF) {
            goto failure;
        }
    }

    for (size_t index = 0; index < count; ++index) {
        free(strings[index]);
    }

    return EXIT_SUCCESS;

failure:
    for (size_t index = 0; index < count; ++index) {
        free(strings[index]);
    }

    return EXIT_FAILURE;
}