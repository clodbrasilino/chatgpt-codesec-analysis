#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
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

    size_t camel_idx = 0;
    const char *ptr = snake_str;
    regmatch_t pmatch[2];

    while (1) {
        ret = regexec(&regex, ptr, 2, pmatch, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = len - (size_t)(ptr - snake_str);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(camel_str + camel_idx, ptr, remaining_len);
            camel_idx += remaining_len;
            break;
        }

        if (ret != 0) {
            free(camel_str);
            regfree(&regex);
            return NULL;
        }

        size_t match_len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(camel_str + camel_idx, ptr, match_len);
        camel_idx += match_len;

        char upper_char = toupper((unsigned char)ptr[pmatch[1].rm_so]);
        camel_str[camel_idx++] = upper_char;

        ptr += pmatch[0].rm_eo;
    }

    camel_str[camel_idx] = '\0';
    regfree(&regex);
    return camel_str;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        const char *test = "hello_world_example";
        char *result = snake_to_camel(test);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        char *result = snake_to_camel(argv[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    return 0;
}