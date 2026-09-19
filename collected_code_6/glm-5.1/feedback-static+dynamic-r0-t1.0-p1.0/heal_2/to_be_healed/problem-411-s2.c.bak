#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t camel_idx = 0;
    size_t i = 0;

    while (snake_str[i] != '\0') {
        if (snake_str[i] == '_') {
            i++;
            if (snake_str[i] != '\0') {
                camel_str[camel_idx++] = toupper((unsigned char)snake_str[i]);
                i++;
            }
        } else {
            camel_str[camel_idx++] = snake_str[i];
            i++;
        }
    }

    camel_str[camel_idx] = '\0';

    char *shrunk = realloc(camel_str, camel_idx + 1);
    if (shrunk != NULL) {
        camel_str = shrunk;
    }

    return camel_str;
}

int main(void) {
    const char *test_cases[] = {
        "android_tv",
        "google_pixel",
        "apple_watch",
        "this_is_a_snake_case_string_123",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *output = snake_to_camel(test_cases[i]);
        if (output == NULL) {
            return 1;
        }
        printf("%s\n", output);
        free(output);
    }

    return 0;
}