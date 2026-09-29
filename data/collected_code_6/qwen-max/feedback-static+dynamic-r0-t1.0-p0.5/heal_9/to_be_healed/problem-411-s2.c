#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) return NULL;
    size_t len = strnlen(snake_str, 1024);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) return NULL;
    snprintf(camel_str, len + 1, "%s", snake_str);

    regex_t regex;
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (int pos = 0; ; ) {
        regmatch_t matches[2];
        int result = regexec(&regex, camel_str + pos, 2, matches, 0);
        if (result != 0) break;
        int match_start = matches[1].rm_so + pos;
        camel_str[match_start] = toupper((unsigned char) camel_str[match_start]);
        memmove(camel_str + match_start - 1, camel_str + match_start, len - match_start + 1);
        --pos;
        --len;
    }

    regfree(&regex);

    camel_str[0] = toupper((unsigned char) camel_str[0]);

    return camel_str;
}

int main() {
    const char *test_cases[] = {"this_is_a_snake_case_string", "android_tv", "apple_watch", "google_pixel"};
    const char *expected_outputs[] = {"ThisIsASnakeCaseString", "AndroidTv", "AppleWatch", "GooglePixel"};
    for (int i = 0; i < 4; ++i) {
        char *camel_str = snake_to_camel(test_cases[i]);
        if (camel_str != NULL) {
            if (strcmp(camel_str, expected_outputs[i]) == 0) {
                printf("%s\n", camel_str);
            } else {
                printf("Test case %d failed: expected '%s', got '%s'\n", i, expected_outputs[i], camel_str);
            }
            free(camel_str);
        } else {
            printf("Error converting string.\n");
        }
    }
    return 0;
}