#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t match[2];

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(camel_str, snake_str, len + 1);

    char *p = camel_str;
    while (regexec(&regex, p, 2, match, 0) == 0) {
        p[match[1].rm_so] = toupper(p[match[1].rm_so]);
        p += match[0].rm_eo;
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *test_cases[] = {"this_is_a_snake_case_string", "android_tv", "google_pixel", "apple_watch"};
    const char *expected_results[] = {"ThisIsASnakeCaseString", "AndroidTv", "GooglePixel", "AppleWatch"};

    for (int i = 0; i < 4; ++i) {
        char *result = snake_to_camel(test_cases[i]);
        if (result != NULL && strcmp(result, expected_results[i]) == 0) {
            printf("%s\n", result);
        } else {
            printf("Conversion failed for: %s, got: %s\n", test_cases[i], result ? result : "<no output>");
        }
        free(result);
    }

    return 0;
}