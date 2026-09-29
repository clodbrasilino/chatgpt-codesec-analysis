#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *camel_to_snake(const char *input)
{
    size_t len;
    size_t extra;
    size_t i;
    size_t j;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);
    extra = 0U;

    for (i = 0U; i < len; i++) {
        if (isupper((unsigned char)input[i]) && i > 0U) {
            extra++;
        }
    }

    output = malloc(len + extra + 1U);
    if (output == NULL) {
        return NULL;
    }

    j = 0U;
    for (i = 0U; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0U) {
                output[j++] = '_';
            }
            output[j++] = (char)tolower((unsigned char)input[i]);
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCase",
        "thisIsALongerExample",
        "simple",
        "convertMePlease"
    };
    size_t num_tests;
    size_t i;

    num_tests = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < num_tests; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], result);
        free(result);
        result = NULL;
    }

    return EXIT_SUCCESS;
}