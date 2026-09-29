#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_concatenation(const char *string, char **repeated)
{
    size_t length;
    size_t unit_length;
    char *result;

    if (string == NULL || repeated == NULL) {
        return false;
    }

    *repeated = NULL;
    length = strlen(string);

    if (length < 2U) {
        return false;
    }

    for (unit_length = 1U; unit_length <= length / 2U; ++unit_length) {
        size_t index;

        if (length % unit_length != 0U) {
            continue;
        }

        for (index = unit_length; index < length; ++index) {
            if (string[index] != string[index % unit_length]) {
                break;
            }
        }

        if (index == length) {
            result = malloc(unit_length + 1U);
            if (result == NULL) {
                return false;
            }

            memcpy(result, string, unit_length);
            result[unit_length] = '\0';
            *repeated = result;
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    char *repeated = NULL;
    bool matches;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    matches = is_concatenation(argv[1], &repeated);

    if (matches) {
        printf("true: %s\n", repeated);
    } else {
        puts("false");
    }

    free(repeated);
    return EXIT_SUCCESS;
}