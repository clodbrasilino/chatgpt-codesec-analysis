#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
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

        size_t index = unit_length;
        while (index < length &&
               string[index] == string[index % unit_length]) {
            ++index;
        }

        if (index == length) {
            if (unit_length > SIZE_MAX - 1U) {
                return false;
            }

            size_t allocation_size = unit_length + 1U;
            char *result = malloc(allocation_size);
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
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t length = strlen(input);
    char *repeated = NULL;

    if (is_concatenation(input, length, &repeated)) {
        printf("true: %s\n", repeated);
    } else {
        puts("false");
    }

    free(repeated);
    return EXIT_SUCCESS;
}