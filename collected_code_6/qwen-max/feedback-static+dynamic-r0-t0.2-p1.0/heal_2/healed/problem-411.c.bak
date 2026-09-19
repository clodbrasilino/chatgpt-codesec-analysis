#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    char *camel_str = strdup(snake_str);
    int len = strlen(camel_str);
    int i, j;

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    i = 0;
    while (i < len) {
        if (regexec(&regex, camel_str + i, 2, matches, 0) == 0) {
            for (j = i + matches[1].rm_so; j < len; ++j) {
                camel_str[j] = camel_str[j + 1];
            }
            camel_str[i + matches[1].rm_so] = toupper(camel_str[i + matches[1].rm_so]);
            --len;
        } else {
            ++i;
        }
    }

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