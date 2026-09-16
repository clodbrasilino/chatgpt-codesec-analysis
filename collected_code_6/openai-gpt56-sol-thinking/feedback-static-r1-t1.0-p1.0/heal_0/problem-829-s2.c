#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FIND_SUCCESS,
    FIND_NOT_FOUND,
    FIND_INVALID_ARGUMENT
} FindStatus;

FindStatus find_second_most_frequent(char *const *strings,
                                    size_t count,
                                    const char **result)
{
    const char *most_frequent = NULL;
    const char *second_most_frequent = NULL;
    size_t highest_frequency = 0;
    size_t second_highest_frequency = 0;

    if (strings == NULL || result == NULL || count == 0) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return FIND_INVALID_ARGUMENT;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t frequency = 1;
        int already_counted = 0;

        for (size_t j = 0; j < i; ++j) {
            if (strcmp(strings[i], strings[j]) == 0) {
                already_counted = 1;
                break;
            }
        }

        if (already_counted != 0) {
            continue;
        }

        for (size_t j = i + 1; j < count; ++j) {
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
    FindStatus status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s string [string ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = find_second_most_frequent(argv + 1, (size_t)(argc - 1), &result);

    if (status == FIND_INVALID_ARGUMENT) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (status == FIND_NOT_FOUND) {
        fprintf(stderr, "No second most frequent string found\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);
    return EXIT_SUCCESS;
}