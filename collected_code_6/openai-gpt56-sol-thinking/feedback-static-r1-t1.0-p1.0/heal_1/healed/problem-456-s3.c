#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool bounded_string_length(const char *string, size_t capacity,
                                  size_t *length)
{
    size_t i;

    if (string == NULL || length == NULL) {
        return false;
    }

    for (i = 0U; i < capacity; ++i) {
        if (string[i] == '\0') {
            *length = i;
            return true;
        }
    }

    return false;
}

static bool reverse_strings(char *const strings[],
                            const size_t capacities[],
                            size_t count)
{
    size_t i;

    if (count > 0U && (strings == NULL || capacities == NULL)) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        size_t length;

        if (!bounded_string_length(strings[i], capacities[i], &length)) {
            return false;
        }
    }

    for (i = 0U; i < count; ++i) {
        size_t left = 0U;
        size_t right;

        if (!bounded_string_length(strings[i], capacities[i], &right)) {
            return false;
        }

        while (left < right) {
            char temporary;

            --right;
            if (left >= right) {
                break;
            }

            temporary = strings[i][left];
            strings[i][left] = strings[i][right];
            strings[i][right] = temporary;
            ++left;
        }
    }

    return true;
}

int main(void)
{
    char first[] = "Hello";
    char second[] = "World";
    char third[] = "C programming";
    char *strings[] = {first, second, third};
    const size_t capacities[] = {
        sizeof(first),
        sizeof(second),
        sizeof(third)
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t i;

    if (!reverse_strings(strings, capacities, count)) {
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (puts(strings[i]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}