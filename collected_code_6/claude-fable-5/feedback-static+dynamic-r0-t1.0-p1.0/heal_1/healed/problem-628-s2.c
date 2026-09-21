#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

char *replace_spaces(const char *input)
{
    size_t len;
    size_t space_count;
    size_t new_len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && input[MAX_INPUT_LEN - 1] != '\0') {
        return NULL;
    }

    space_count = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            space_count++;
        }
    }

    if (space_count > (SIZE_MAX - len - 1) / 2) {
        return NULL;
    }

    new_len = len + (space_count * 2);

    result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == ' ') {
            result[j] = '%';
            result[j + 1] = '2';
            result[j + 2] = '0';
            j += 3;
        } else {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello World",
        "  leading and trailing  ",
        "nospace",
        ""
    };
    size_t count;
    size_t i;

    count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0; i < count; i++) {
        char *converted = replace_spaces(test_strings[i]);
        if (converted == NULL) {
            fprintf(stderr, "Conversion failed for input: \"%s\"\n",
                    test_strings[i]);
            return EXIT_FAILURE;
        }
        if (printf("Input: \"%s\" -> Output: \"%s\"\n",
                   test_strings[i], converted) < 0) {
            free(converted);
            return EXIT_FAILURE;
        }
        free(converted);
    }

    return EXIT_SUCCESS;
}