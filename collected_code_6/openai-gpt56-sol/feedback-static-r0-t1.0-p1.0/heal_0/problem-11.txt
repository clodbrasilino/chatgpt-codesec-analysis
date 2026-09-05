#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_first_and_last(const char *str, char target)
{
    size_t length;
    size_t first = SIZE_MAX;
    size_t last = SIZE_MAX;
    size_t output_length;
    size_t source_index;
    size_t destination_index = 0;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    length = strlen(str);

    for (source_index = 0; source_index < length; ++source_index) {
        if (str[source_index] == target) {
            if (first == SIZE_MAX) {
                first = source_index;
            }
            last = source_index;
        }
    }

    output_length = length;
    if (first != SIZE_MAX) {
        --output_length;
        if (last != first) {
            --output_length;
        }
    }

    result = malloc(output_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (source_index = 0; source_index < length; ++source_index) {
        if (source_index != first && source_index != last) {
            result[destination_index++] = str[source_index];
        }
    }

    result[destination_index] = '\0';
    return result;
}

int main(void)
{
    char input[1024];
    char target;
    char *newline;
    char *result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    newline = strchr(input, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    if (scanf(" %c", &target) != 1) {
        return EXIT_FAILURE;
    }

    result = remove_first_and_last(input, target);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}