#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input);

char *camel_to_snake(const char *input)
{
    char *output = NULL;
    size_t in_len = 0;
    size_t out_len = 0;
    size_t out_cap = 0;
    size_t i = 0;

    if (input == NULL) {
        return NULL;
    }

    while (in_len < MAX_INPUT_LEN && input[in_len] != '\0') {
        in_len++;
    }

    if (in_len >= MAX_INPUT_LEN && input[in_len] != '\0') {
        return NULL;
    }

    out_cap = (in_len * 2U) + 1U;
    output = (char *)malloc(out_cap);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < in_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (isupper((int)c) != 0) {
            if (i > 0U && out_len < (out_cap - 1U)) {
                output[out_len] = '_';
                out_len++;
            }
            if (out_len < (out_cap - 1U)) {
                output[out_len] = (char)tolower((int)c);
                out_len++;
            }
        } else {
            if (out_len < (out_cap - 1U)) {
                output[out_len] = (char)c;
                out_len++;
            }
        }
    }

    output[out_len] = '\0';

    return output;
}

int main(void)
{
    const char *tests[] = {
        "GoogleAssistant",
        "ChromeCast",
        "QuadCore",
        "camelCaseString",
        "ThisIsATest",
        "already_snake",
        "simpleXMLParser",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i = 0;
    int status = EXIT_SUCCESS;

    for (i = 0; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            (void)fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            status = EXIT_FAILURE;
            continue;
        }
        (void)printf("%s\n", result);
        (void)fflush(stdout);
        free(result);
        result = NULL;
    }

    return status;
}