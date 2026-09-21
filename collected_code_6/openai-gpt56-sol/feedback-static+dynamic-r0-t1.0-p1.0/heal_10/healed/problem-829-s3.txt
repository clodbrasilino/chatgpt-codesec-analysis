#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static int find_second_most_frequent(const char *const strings[],
                                     const size_t lengths[],
                                     size_t count,
                                     char **result)
{
    char **unique_strings = NULL;
    size_t *unique_lengths = NULL;
    size_t *frequencies = NULL;
    size_t unique_count = 0U;
    size_t highest = 0U;
    size_t second_highest = 0U;
    size_t second_index = 0U;
    size_t i;
    int status = -1;

    if (strings == NULL || lengths == NULL || result == NULL || count == 0U) {
        return -1;
    }

    *result = NULL;

    if (count > SIZE_MAX / sizeof(*unique_strings) ||
        count > SIZE_MAX / sizeof(*unique_lengths) ||
        count > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    unique_strings = calloc(count, sizeof(*unique_strings));
    unique_lengths = calloc(count, sizeof(*unique_lengths));
    frequencies = calloc(count, sizeof(*frequencies));

    if (unique_strings == NULL ||
        unique_lengths == NULL ||
        frequencies == NULL) {
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        const char *terminator;
        size_t current_length;
        size_t j;

        if (strings[i] == NULL || lengths[i] == 0U) {
            goto cleanup;
        }

        terminator = memchr(strings[i], '\0', lengths[i]);
        if (terminator == NULL) {
            goto cleanup;
        }

        current_length = (size_t)(terminator - strings[i]);

        for (j = 0U; j < unique_count; ++j) {
            if (current_length == unique_lengths[j] &&
                (current_length == 0U ||
                 memcmp(strings[i], unique_strings[j], current_length) == 0)) {
                if (frequencies[j] == SIZE_MAX) {
                    goto cleanup;
                }

                ++frequencies[j];
                break;
            }
        }

        if (j == unique_count) {
            char *new_string;

            if (unique_count >= count) {
                goto cleanup;
            }

            new_string = duplicate_string(strings[i], current_length);
            if (new_string == NULL) {
                goto cleanup;
            }

            unique_strings[unique_count] = new_string;
            unique_lengths[unique_count] = current_length;
            frequencies[unique_count] = 1U;
            ++unique_count;
        }
    }

    for (i = 0U; i < unique_count; ++i) {
        if (frequencies[i] > highest) {
            highest = frequencies[i];
        }
    }

    for (i = 0U; i < unique_count; ++i) {
        if (frequencies[i] < highest &&
            frequencies[i] > second_highest) {
            second_highest = frequencies[i];
            second_index = i;
        }
    }

    if (second_highest == 0U) {
        status = 0;
        goto cleanup;
    }

    *result = duplicate_string(unique_strings[second_index],
                               unique_lengths[second_index]);
    if (*result == NULL) {
        goto cleanup;
    }

    status = 1;

cleanup:
    if (unique_strings != NULL) {
        for (i = 0U; i < unique_count; ++i) {
            free(unique_strings[i]);
        }
    }

    free(unique_strings);
    free(unique_lengths);
    free(frequencies);

    return status;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";
    static const char grape[] = "grape";

    const char *strings[] = {
        apple,
        banana,
        apple,
        orange,
        banana,
        apple,
        grape,
        banana,
        orange,
        banana
    };

    const size_t lengths[] = {
        sizeof apple,
        sizeof banana,
        sizeof apple,
        sizeof orange,
        sizeof banana,
        sizeof apple,
        sizeof grape,
        sizeof banana,
        sizeof orange,
        sizeof banana
    };

    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *result = NULL;
    int status;

    if (count != sizeof(lengths) / sizeof(lengths[0])) {
        return EXIT_FAILURE;
    }

    status = find_second_most_frequent(strings, lengths, count, &result);

    if (status < 0) {
        fputs("Unable to determine the result.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 0) {
        puts("No second most frequent string exists.");
        return EXIT_SUCCESS;
    }

    puts(result);
    free(result);

    return EXIT_SUCCESS;
}