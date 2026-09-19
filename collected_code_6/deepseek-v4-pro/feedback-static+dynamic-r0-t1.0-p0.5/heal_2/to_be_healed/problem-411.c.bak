#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strlen(snake);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    int capitalize_next = 0;

    if (snake[0] != '\0') {
        result[dst_pos++] = snake[0];
        src_pos = 1;
    }

    while (src_pos < len) {
        if (snake[src_pos] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[dst_pos++] = toupper((unsigned char)snake[src_pos]);
                capitalize_next = 0;
            } else {
                result[dst_pos++] = snake[src_pos];
            }
        }
        src_pos++;
    }

    result[dst_pos] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string",
        "convert_this_to_camel",
        "already_camel",
        "multiple__underscores",
        "trailing_underscore_",
        "_leading_underscore",
        "single",
        "",
        "android_tv",
        "google_pixel",
        "apple_watch",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *camel = snake_to_camel(test_cases[i]);
        if (camel != NULL) {
            printf("%s -> %s\n", test_cases[i], camel);
            free(camel);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}