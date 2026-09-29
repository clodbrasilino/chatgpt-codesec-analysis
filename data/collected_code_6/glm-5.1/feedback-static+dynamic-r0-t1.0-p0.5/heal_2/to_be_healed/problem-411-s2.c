#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t matches[2];
    int ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t camel_idx = 0;
    const char *cursor = snake_str;

    while (1) {
        ret = regexec(&regex, cursor, 2, matches, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = matches[0].rm_so;
        if (camel_idx + prefix_len >= len + 1) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(camel_str + camel_idx, cursor, prefix_len);
        camel_idx += prefix_len;

        if (camel_idx >= len + 1) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }
        char lower_char = cursor[matches[1].rm_so];
        camel_str[camel_idx++] = lower_char - 'a' + 'A';

        cursor += matches[0].rm_eo;
    }

    size_t remaining_len = 0;
    while (cursor[remaining_len] != '\0') {
        remaining_len++;
    }
    if (camel_idx + remaining_len >= len + 1) {
        free(camel_str);
        regfree(&regex);
        return NULL;
    }
    snprintf(camel_str + camel_idx, len + 1 - camel_idx, "%s", cursor);

    regfree(&regex);
    return camel_str;
}

int main(void) {
    const char *input0 = "android_tv";
    char *output0 = snake_to_camel(input0);
    if (output0 != NULL) {
        printf("%s\n", output0);
        free(output0);
    }

    const char *input1 = "google_pixel";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    }

    const char *input2 = "apple_watch";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    }

    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}