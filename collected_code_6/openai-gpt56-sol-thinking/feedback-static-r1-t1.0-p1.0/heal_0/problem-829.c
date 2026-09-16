#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FIND_SUCCESS,
    FIND_NOT_FOUND,
    FIND_INVALID_ARGUMENT
} FindResult;

FindResult find_second_most_frequent(
    const char *const strings[],
    size_t count,
    const char **result
) {
    size_t highest_frequency = 0;
    size_t second_frequency = 0;
    size_t second_index = 0;

    if (result == NULL || (strings == NULL && count != 0)) {
        return FIND_INVALID_ARGUMENT;
    }

    *result = NULL;

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return FIND_INVALID_ARGUMENT;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        size_t frequency = 0;
        int already_processed = 0;

        for (size_t j = 0; j < i; ++j) {
            if (strcmp(strings[i], strings[j]) == 0) {
                already_processed = 1;
                break;
            }
        }

        if (already_processed != 0) {
            continue;
        }

        for (size_t j = 0; j < count; ++j) {
            if (strcmp(strings[i], strings[j]) == 0) {
                ++frequency;
            }
        }

        if (frequency > highest_frequency) {
            if (highest_frequency != 0) {
                second_frequency = highest_frequency;
                for (size_t j = 0; j < i; ++j) {
                    size_t previous_frequency = 0;

                    for (size_t k = 0; k < count; ++k) {
                        if (strcmp(strings[j], strings[k]) == 0) {
                            ++previous_frequency;
                        }
                    }

                    if (previous_frequency == second_frequency) {
                        second_index = j;
                        break;
                    }
                }
            }

            highest_frequency = frequency;
        } else if (frequency < highest_frequency &&
                   frequency > second_frequency) {
            second_frequency = frequency;
            second_index = i;
        }
    }

    if (second_frequency == 0) {
        return FIND_NOT_FOUND;
    }

    *result = strings[second_index];
    return FIND_SUCCESS;
}

int main(void) {
    const char *sequence[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple",
        "grape"
    };
    const char *result = NULL;
    const size_t count = sizeof(sequence) / sizeof(sequence[0]);
    const FindResult status =
        find_second_most_frequent(sequence, count, &result);

    if (status == FIND_INVALID_ARGUMENT) {
        if (fputs("Invalid argument\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (status == FIND_NOT_FOUND) {
        if (fputs("No second most frequent string\n", stdout) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("%s\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}