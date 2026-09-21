#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) return NULL;
    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (!camel_str) return NULL;
    memcpy(camel_str, snake_str, len + 1);

    regex_t regex;
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (size_t i = 0; i < len; ) {
        regmatch_t matches[2];
        if (regexec(&regex, camel_str + i, 2, matches, 0) == 0) {
            for (size_t j = i + matches[1].rm_so + 1; j < len; ++j) {
                camel_str[j - 1] = camel_str[j];
            }
            camel_str[i + matches[1].rm_so] = toupper(camel_str[i + matches[1].rm_so]);
            --len;
            i += matches[1].rm_so;
        } else {
            i++;
        }
    }

    if (len > 0)
        camel_str[0] = toupper(camel_str[0]);

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *test_cases[] = {"this_is_a_snake_case_string", "android_tv", "google_pixel", "apple_watch"};
    const char *expected_results[] = {"ThisIsASnakeCaseString", "AndroidTv", "GooglePixel", "AppleWatch"};
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        char *camel_str = snake_to_camel(test_cases[i]);
        if (camel_str) {
            printf("Input: %s, Camel case: %s\n", test_cases[i], camel_str);
            if (strcmp(camel_str, expected_results[i]) != 0) {
                printf("Test failed: expected '%s', got '%s'\n", expected_results[i], camel_str);
            }
            free(camel_str);
        } else {
            printf("Failed to convert to camel case: %s\n", test_cases[i]);
        }
    }

    return 0;
}