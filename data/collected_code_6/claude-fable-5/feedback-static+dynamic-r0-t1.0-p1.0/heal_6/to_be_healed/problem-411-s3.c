#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

char *snake_to_camel(const char *input)
{
    size_t len;
    size_t i;
    size_t out_pos;
    char *result;
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
        char c = input[i];

        if (c == '_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next != 0) {
            result[out_pos] = (char)toupper((unsigned char)c);
            capitalize_next = 0;
        } else {
            result[out_pos] = c;
        }
        out_pos++;
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
        "hello_world",
        "convert_snake_case_to_camel_case",
        "already",
        "multiple__underscores",
        "trailing_"
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        char *converted = snake_to_camel(tests[i]);
        if (converted == NULL) {
            fprintf(stderr, "Conversion failed for: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s\n", converted);
        free(converted);
    }

    return EXIT_SUCCESS;
}