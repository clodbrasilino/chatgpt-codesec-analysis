#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

char *snake_to_camel(const char *input)
{
    char *result;
    size_t len;
    size_t i;
    size_t out_pos;
    int capitalize_next;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    out_pos = 0U;
    capitalize_next = 1;

    for (i = 0U; i < len; i++) {
        if (input[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next && isalpha((unsigned char)input[i])) {
                result[out_pos] = (char)toupper((unsigned char)input[i]);
            } else {
                result[out_pos] = input[i];
            }
            out_pos++;
            capitalize_next = 0;
        }
    }

    result[out_pos] = '\0';
    return result;
}

int main(void)
{
    const char *tests[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "hello_world_example",
        "convert_this_snake_case",
        "single",
        "a_b_c_d"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0U; i < count; i++) {
        char *camel = snake_to_camel(tests[i]);
        if (camel == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s\n", camel) < 0) {
            free(camel);
            return EXIT_FAILURE;
        }
        free(camel);
    }

    return EXIT_SUCCESS;
}