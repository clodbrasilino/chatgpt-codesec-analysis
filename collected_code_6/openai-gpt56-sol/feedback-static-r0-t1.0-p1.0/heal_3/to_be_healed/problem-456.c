#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int reverse_string(char *string, size_t capacity, size_t length)
{
    if (string == NULL || length >= capacity || string[length] != '\0') {
        return -1;
    }

    for (size_t left = 0, right = length; left < right; ++left) {
        char temporary = string[left];

        --right;
        string[left] = string[right];
        string[right] = temporary;
    }

    return 0;
}

static int reverse_strings(char *const strings[],
                           const size_t capacities[],
                           const size_t lengths[],
                           size_t count)
{
    if (count != 0U &&
        (strings == NULL || capacities == NULL || lengths == NULL)) {
        return -1;
    }

    for (size_t index = 0; index < count; ++index) {
        if (reverse_string(strings[index], capacities[index],
                           lengths[index]) != 0) {
            return -1;
        }
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
    static const size_t lengths[] = {
        sizeof("Hello") - 1U,
        sizeof("World") - 1U,
        sizeof("Secure C") - 1U
    };
    enum {
        STRING_COUNT = sizeof(source_strings) / sizeof(source_strings[0])
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *strings[STRING_COUNT] = { NULL };
    size_t capacities[STRING_COUNT] = { 0U };

    for (size_t index = 0; index < STRING_COUNT; ++index) {
        if (lengths[index] == SIZE_MAX) {
            goto failure;
        }

        capacities[index] = lengths[index] + 1U;
        strings[index] = malloc(capacities[index]);
        if (strings[index] == NULL) {
            goto failure;
        }

        if (snprintf(strings[index], capacities[index], "%s",
                     source_strings[index]) < 0 ||
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strlen(strings[index]) != lengths[index]) {
            goto failure;
        }
    }

    if (reverse_strings(strings, capacities, lengths, STRING_COUNT) != 0) {
        goto failure;
    }

    for (size_t index = 0; index < STRING_COUNT; ++index) {
        if (puts(strings[index]) == EOF) {
            goto failure;
        }
    }

    for (size_t index = 0; index < STRING_COUNT; ++index) {
        free(strings[index]);
    }

    return EXIT_SUCCESS;

failure:
    for (size_t index = 0; index < STRING_COUNT; ++index) {
        free(strings[index]);
    }

    return EXIT_FAILURE;
}