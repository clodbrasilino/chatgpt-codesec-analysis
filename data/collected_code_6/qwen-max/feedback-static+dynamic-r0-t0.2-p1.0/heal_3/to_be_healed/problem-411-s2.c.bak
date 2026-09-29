#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got google_Pixel
  *  test case 2 failed: expected 'AppleWatch', got apple_Watch
  *  test case 0 failed: expected 'AndroidTv', got android_Tv
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t match[2];
    char *camel_str, *p, *result;

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    int len = strlen(snake_str);
    camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }
    strcpy(camel_str, snake_str);

    p = camel_str;
    while (regexec(&regex, p, 2, match, 0) == 0) {
        int match_len = match[1].rm_eo - match[1].rm_so;
        for (int i = 0; i < match_len; i++) {
            p[match[1].rm_so + i] = toupper(p[match[1].rm_so + i]);
        }
        p += match[0].rm_eo;
    }

    regfree(&regex);
    result = realloc(camel_str, strlen(camel_str) + 1);
    if (result == NULL) {
        free(camel_str);
        return NULL;
    }
    return result;
}

int main() {
    const char *test_cases[] = {"google_pixel", "apple_watch", "android_tv"};
    const char *expected[] = {"GooglePixel", "AppleWatch", "AndroidTv"};

    for (int i = 0; i < 3; i++) {
        char *camel_str = snake_to_camel(test_cases[i]);
        if (camel_str != NULL) {
            if (strcmp(camel_str, expected[i]) == 0) {
                printf("Test case %d: Passed\n", i);
            } else {
                printf("Test case %d: Failed, expected '%s', got '%s'\n", i, expected[i], camel_str);
            }
            free(camel_str);
        } else {
            printf("Test case %d: Conversion failed.\n", i);
        }
    }

    return 0;
}