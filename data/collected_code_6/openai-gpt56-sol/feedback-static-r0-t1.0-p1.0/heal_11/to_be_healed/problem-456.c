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
    static const char source_0[] = "Hello";
    static const char source_1[] = "World";
    static const char source_2[] = "Secure C";

    static const struct {
        const char *data;
        size_t length;
    } sources[] = {
        { source_0, sizeof(source_0) - 1U },
        { source_1, sizeof(source_1) - 1U },
        { source_2, sizeof(source_2) - 1U }
    };

    const size_t count = sizeof(sources) / sizeof(sources[0]);
    char **strings = NULL;
    size_t *capacities = NULL;
    size_t *lengths = NULL;
    int status = EXIT_FAILURE;

    if (count > SIZE_MAX / sizeof(*strings) ||
        count > SIZE_MAX / sizeof(*capacities) ||
        count > SIZE_MAX / sizeof(*lengths)) {
        goto cleanup;
    }

    strings = calloc(count, sizeof(*strings));
    capacities = calloc(count, sizeof(*capacities));
    lengths = calloc(count, sizeof(*lengths));

    if (strings == NULL || capacities == NULL || lengths == NULL) {
        goto cleanup;
    }

    for (size_t index = 0U; index < count; ++index) {
        size_t capacity;

        if (sources[index].length == SIZE_MAX) {
            goto cleanup;
        }

        capacity = sources[index].length + 1U;
        strings[index] = malloc(capacity);

        if (strings[index] == NULL) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[index], sources[index].data, capacity);
        capacities[index] = capacity;
        lengths[index] = sources[index].length;
    }

    if (reverse_strings(strings, capacities, lengths, count) != 0) {
        goto cleanup;
    }

    for (size_t index = 0U; index < count; ++index) {
        if (puts(strings[index]) == EOF) {
            goto cleanup;
        }
    }

    status = EXIT_SUCCESS;

cleanup:
    if (strings != NULL) {
        for (size_t index = 0U; index < count; ++index) {
            free(strings[index]);
        }
    }

    free(lengths);
    free(capacities);
    free(strings);

    return status;
}