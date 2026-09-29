#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 4096

char *snake_to_camel(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    int upper_next;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH) {
        return NULL;
    }

    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    upper_next = 1;
    for (i = 0; i < len; i++) {
        if (input[i] == '_') {
            upper_next = 1;
        } else if (upper_next) {
            result[j++] = (char)toupper((unsigned char)input[i]);
            upper_next = 0;
        } else {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *tests[] = {
        "python_program",
        "python_language",
        "programming_language"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t k;

    for (k = 0; k < num_tests; k++) {
        char *camel = snake_to_camel(tests[k]);
        if (camel == NULL) {
            fprintf(stderr, "Error: failed to convert \"%s\"\n", tests[k]);
            return EXIT_FAILURE;
        }
        printf("%s\n", camel);
        free(camel);
        camel = NULL;
    }

    return EXIT_SUCCESS;
}