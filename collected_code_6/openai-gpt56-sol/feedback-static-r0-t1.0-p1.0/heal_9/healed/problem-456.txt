#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int reverse_string(char *string, size_t capacity, size_t length)
{
    if (string == NULL || capacity == 0U || length >= capacity ||
        string[length] != '\0') {
        return -1;
    }

    for (size_t left = 0U, right = length; left < right; ++left) {
        char temporary;

        --right;
        temporary = string[left];
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
    if (count > 0U &&
        (strings == NULL || capacities == NULL || lengths == NULL)) {
        return -1;
    }

    for (size_t index = 0U; index < count; ++index) {
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
    enum {
        STRING_COUNT = sizeof(source_strings) / sizeof(source_strings[0])
    };

    char **strings = NULL;
    size_t *capacities = NULL;
    size_t *lengths = NULL;
    int status = EXIT_FAILURE;

    if ((size_t)STRING_COUNT > SIZE_MAX / sizeof(*strings) ||
        (size_t)STRING_COUNT > SIZE_MAX / sizeof(*capacities) ||
        (size_t)STRING_COUNT > SIZE_MAX / sizeof(*lengths)) {
        goto cleanup;
    }

    strings = calloc((size_t)STRING_COUNT, sizeof(*strings));
    capacities = calloc((size_t)STRING_COUNT, sizeof(*capacities));
    lengths = calloc((size_t)STRING_COUNT, sizeof(*lengths));

    if (strings == NULL || capacities == NULL || lengths == NULL) {
        goto cleanup;
    }

    for (size_t index = 0U; index < (size_t)STRING_COUNT; ++index) {
        const size_t length = strlen(source_strings[index]);
        size_t destination_capacity;

        if (length == SIZE_MAX) {
            goto cleanup;
        }

        destination_capacity = length + 1U;
        strings[index] = malloc(destination_capacity);
        if (strings[index] == NULL) {
            goto cleanup;
        }

        if (snprintf(strings[index], destination_capacity, "%s",
                     source_strings[index]) < 0 ||
            strings[index][length] != '\0') {
            goto cleanup;
        }

        capacities[index] = destination_capacity;
        lengths[index] = length;
    }

    if (reverse_strings(strings, capacities, lengths,
                        (size_t)STRING_COUNT) != 0) {
        goto cleanup;
    }

    for (size_t index = 0U; index < (size_t)STRING_COUNT; ++index) {
        if (puts(strings[index]) == EOF) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    if (strings != NULL) {
        for (size_t index = 0U; index < (size_t)STRING_COUNT; ++index) {
            free(strings[index]);
        }
    }

    free(lengths);
    free(capacities);
    free(strings);

    return status;
}