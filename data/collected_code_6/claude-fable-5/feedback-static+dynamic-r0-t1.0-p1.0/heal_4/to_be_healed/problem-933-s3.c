#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *camel_to_snake(const char *input);
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
  */

char *camel_to_snake(const char *input)
{
    char *output = NULL;
    size_t input_len;
    size_t out_capacity;
    size_t out_len = 0;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (input_len > ((SIZE_MAX - 1U) / 2U)) {
        return NULL;
    }
    out_capacity = (input_len * 2U) + 1U;

    output = malloc(out_capacity);
    if (output == NULL) {
        return NULL;
    }

    for (i = 0; i < input_len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (isupper(c)) {
            if (i > 0U) {
                if (out_len >= (out_capacity - 1U)) {
                    free(output);
                    return NULL;
                }
                output[out_len] = '_';
                out_len++;
            }
            if (out_len >= (out_capacity - 1U)) {
                free(output);
                return NULL;
            }
            output[out_len] = (char)tolower(c);
            out_len++;
        } else {
            if (out_len >= (out_capacity - 1U)) {
                free(output);
                return NULL;
            }
            output[out_len] = (char)c;
            out_len++;
        }
    }

    if (out_len >= out_capacity) {
        free(output);
        return NULL;
    }

    output[out_len] = '\0';
    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "ConvertThisToSnake",
        "alreadylower",
        "XMLParser",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
        free(result);
    }

    return EXIT_SUCCESS;
}