#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    int len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    int i, j, match_pos;

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    for (i = 0, j = 0; i < len; ++i, ++j) {
        camel_str[j] = snake_str[i];
        if (snake_str[i] == '_') {
            if (regexec(&regex, snake_str + i, 2, matches, 0) == 0) {
                match_pos = matches[1].rm_so + i;
                camel_str[j] = toupper(snake_str[match_pos]);
                ++i;
            }
        } else if (i == 0 || (i > 1 && snake_str[i - 1] == '_')) {
            camel_str[j] = toupper(snake_str[i]);
        }
    }
    camel_str[j] = '\0';

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *test_cases[] = {"android_tv", "google_pixel", "apple_watch"};
    const char *expected_results[] = {"AndroidTv", "GooglePixel", "AppleWatch"};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; ++i) {
        char *camel_str = snake_to_camel(test_cases[i]);
        if (camel_str) {
            printf("Test case %d: %s -> %s\n", i, test_cases[i], camel_str);
            if (strcmp(camel_str, expected_results[i]) == 0) {
                printf("Test case %d passed.\n", i);
            } else {
                printf("Test case %d failed: expected '%s', got '%s'\n", i, expected_results[i], camel_str);
            }
            free(camel_str);
        } else {
            printf("Failed to convert test case %d to camel case.\n", i);
        }
    }

    return 0;
}