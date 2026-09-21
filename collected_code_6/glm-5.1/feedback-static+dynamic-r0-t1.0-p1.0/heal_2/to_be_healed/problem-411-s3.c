#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got <no output>
  *  test case 1 failed: expected 'GooglePixel', got <no output>
  *  test case 0 failed: expected 'AndroidTv', got <no output>
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) return NULL;

    regex_t regex;
    regmatch_t matches[2];
    int ret;

    ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') len++;

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t i = 0;
    const char *cursor = snake_str;

    while (1) {
        ret = regexec(&regex, cursor, 2, matches, 0);
        if (ret == REG_NOMATCH || matches[0].rm_so == -1 || matches[1].rm_so == -1) {
            size_t remaining = len - (cursor - snake_str);
            if (remaining > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(camel_str + i, cursor, remaining);
                i += remaining;
            }
            camel_str[i] = '\0';
            break;
        }

        size_t copy_len = matches[0].rm_so;
        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(camel_str + i, cursor, copy_len);
            i += copy_len;
        }

        if (cursor[matches[1].rm_so] >= 'a' && cursor[matches[1].rm_so] <= 'z') {
            camel_str[i++] = cursor[matches[1].rm_so] - 32;
        } else {
            camel_str[i++] = cursor[matches[1].rm_so];
        }

        cursor += matches[0].rm_eo;
    }

    regfree(&regex);
    return camel_str;
}

int main(void) {
    const char *tests[] = {"android_tv", "google_pixel", "apple_watch", "convert_this_snake_case_string", NULL};
    
    for (int i = 0; tests[i] != NULL; i++) {
        char *output = snake_to_camel(tests[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Conversion failed\n");
            return 1;
        }
    }

    return 0;
}