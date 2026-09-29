#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FIND_SUCCESS,
    FIND_INVALID_ARGUMENT,
    FIND_NOT_FOUND
} FindResult;

FindResult find_second_most_frequent_string(
    const char *const strings[],
    size_t count,
    const char **result)
{
    const char *most_frequent = NULL;
    const char *second_most_frequent = NULL;
    size_t highest_frequency = 0;
    size_t second_highest_frequency = 0;

    if (strings == NULL || result == NULL) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;

    for (size_t i = 0; i < count; ++i) {
        size_t frequency = 0;
        int previously_counted = 0;

        if (strings[i] == NULL) {
            return FIND_INVALID_ARGUMENT;
        }

        for (size_t j = 0; j < i; ++j) {
            if (strcmp(strings[i], strings[j]) == 0) {
                previously_counted = 1;
                break;
            }
        }

        if (previously_counted) {
            continue;
        }

        for (size_t j = 0; j < count; ++j) {
            if (strings[j] == NULL) {
                return FIND_INVALID_ARGUMENT;
            }

            if (strcmp(strings[i], strings[j]) == 0) {
                ++frequency;
            }
        }

        if (frequency > highest_frequency) {
            second_highest_frequency = highest_frequency;
            second_most_frequent = most_frequent;
            highest_frequency = frequency;
            most_frequent = strings[i];
        } else if (frequency < highest_frequency &&
                   frequency > second_highest_frequency) {
            second_highest_frequency = frequency;
            second_most_frequent = strings[i];
        }
    }

    if (second_most_frequent == NULL) {
        return FIND_NOT_FOUND;
    }

    *result = second_most_frequent;
    return FIND_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *result = NULL;
    FindResult status;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s string1 string2 [string3 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = find_second_most_frequent_string(
        (const char *const *)&argv[1],
        (size_t)(argc - 1),
        &result);

    if (status == FIND_INVALID_ARGUMENT) {
        fprintf(stderr, "Invalid argument\n");
        return EXIT_FAILURE;
    }

    if (status == FIND_NOT_FOUND) {
        fprintf(stderr, "No second most frequent string found\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    return EXIT_SUCCESS;
}