#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input)
{
    char *output;
    size_t in_len;
    size_t out_len;
    size_t out_pos;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    in_len = strnlen(input, MAX_INPUT_LEN);
    if (in_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    out_len = (in_len * 2U) + 1U;
    output = malloc(out_len);
    if (output == NULL) {
        return NULL;
    }

    out_pos = 0U;

    for (i = 0U; i < in_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (isupper(c)) {
            if (i > 0U) {
                if ((out_pos + 2U) >= out_len) {
                    free(output);
                    return NULL;
                }
                output[out_pos] = '_';
                out_pos++;
            } else {
                if ((out_pos + 1U) >= out_len) {
                    free(output);
                    return NULL;
                }
            }
            output[out_pos] = (char)tolower(c);
            out_pos++;
        } else {
            if ((out_pos + 1U) >= out_len) {
                free(output);
                return NULL;
            }
            output[out_pos] = (char)c;
            out_pos++;
        }
    }

    if (out_pos >= out_len) {
        free(output);
        return NULL;
    }
    output[out_pos] = '\0';

    return output;
}

int main(void)
{
    const char *tests[] = {
        "googleAssistant",
        "quadCore",
        "chromeCast",
        "camelCaseString",
        "helloWorldExample",
        "alreadysnake",
        "MixedUPCase"
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            (void)fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s\n", result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
        free(result);
    }

    return EXIT_SUCCESS;
}