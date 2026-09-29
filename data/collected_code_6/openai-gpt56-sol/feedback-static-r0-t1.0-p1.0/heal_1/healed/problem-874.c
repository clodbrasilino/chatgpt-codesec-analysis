#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_concatenation(const char *string, size_t length, char **repeated)
{
    if (string == NULL || repeated == NULL) {
        return false;
    }

    *repeated = NULL;

    if (length < 2U) {
        return false;
    }

    for (size_t unit_length = 1U; unit_length <= length / 2U; ++unit_length) {
        if (length % unit_length != 0U) {
            continue;
        }

        size_t index;
        for (index = unit_length; index < length; ++index) {
            if (string[index] != string[index % unit_length]) {
                break;
            }
        }

        if (index == length) {
            if (unit_length == SIZE_MAX) {
                return false;
            }

            char *result = malloc(unit_length + 1U);
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
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    const size_t input_length = strlen(input);
    char *repeated = NULL;
    const bool matches = is_concatenation(input, input_length, &repeated);

    if (matches) {
        printf("true: %s\n", repeated);
    } else {
        puts("false");
    }

    free(repeated);
    return EXIT_SUCCESS;
}