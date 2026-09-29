#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        free(camel_str);
        return NULL;
    }

    char *out_ptr = camel_str;
    const char *in_ptr = snake_str;
    regmatch_t matches[2];

    while (1) {
        ret = regexec(&regex, in_ptr, 2, matches, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = 0;
            while (in_ptr[remaining_len] != '\0') {
                remaining_len++;
            }
            if (remaining_len > 0 && (size_t)(out_ptr - camel_str) + remaining_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(out_ptr, in_ptr, remaining_len);
                out_ptr += remaining_len;
            }
            break;
        }

        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = matches[0].rm_so;
        if (prefix_len > 0 && (size_t)(out_ptr - camel_str) + prefix_len <= len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(out_ptr, in_ptr, prefix_len);
            out_ptr += prefix_len;
        }

        if (matches[1].rm_so != -1 && (size_t)(out_ptr - camel_str) < len) {
            char c = in_ptr[matches[1].rm_so];
            if (c >= 'a' && c <= 'z') {
                c -= 32;
            }
            *out_ptr = c;
            out_ptr += 1;
        }

        in_ptr += matches[0].rm_eo;
    }

    *out_ptr = '\0';
    regfree(&regex);
    return camel_str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
        return 1;
    }

    char *result = snake_to_camel(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);
    return 0;
}