#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length);
    copy[length] = '\0';

    return copy;
}

static int find_second_most_frequent(const char *const strings[],
                                     const size_t lengths[],
                                     size_t count,
                                     char **result)
{
    char **unique_strings = NULL;
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
        count > SIZE_MAX / sizeof(*frequencies)) {
        return -1;
    }

    unique_strings = calloc(count, sizeof(*unique_strings));
    frequencies = calloc(count, sizeof(*frequencies));

    if (unique_strings == NULL || frequencies == NULL) {
        goto cleanup;
    }

    for (i = 0U; i < count; ++i) {
        char *current;
        size_t j;

        if (strings[i] == NULL || lengths[i] == 0U) {
            goto cleanup;
        }

        current = duplicate_string(strings[i], lengths[i]);
        if (current == NULL) {
            goto cleanup;
        }

        for (j = 0U; j < unique_count; ++j) {
            if (strcmp(current, unique_strings[j]) == 0) {
                if (frequencies[j] == SIZE_MAX) {
                    free(current);
                    goto cleanup;
                }

                ++frequencies[j];
                free(current);
                break;
            }
        }

        if (j == unique_count) {
            unique_strings[unique_count] = current;
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
                               strlen(unique_strings[second_index]) + 1U);
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
        apple, banana, apple, orange, banana,
        apple, grape, banana, orange, banana
    };

    const size_t lengths[] = {
        sizeof(apple), sizeof(banana), sizeof(apple), sizeof(orange),
        sizeof(banana), sizeof(apple), sizeof(grape), sizeof(banana),
        sizeof(orange), sizeof(banana)
    };

    const size_t count = sizeof(strings) / sizeof(strings[0]);
    char *result = NULL;
    int status;

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