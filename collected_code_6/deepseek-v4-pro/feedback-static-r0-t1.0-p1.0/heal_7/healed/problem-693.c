#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_multiple_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, " +", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    
    if (len >= SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *src = input;
    char *dst = result;
    size_t dst_capacity = len + 1;
    size_t dst_used = 0;
    regmatch_t match;

    while (regexec(&regex, src, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            if (match_start > dst_capacity - dst_used) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(dst, src, match_start);
            dst += match_start;
            dst_used += match_start;
        }

        if (dst_capacity - dst_used < 2) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        *dst++ = ' ';
        dst_used++;

        src += match_end;
    }

    size_t remaining = strnlen(src, SIZE_MAX);

    if (remaining + 1 > dst_capacity - dst_used) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    memcpy(dst, src, remaining + 1);

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test = "This  is   a    test   string";
    char *cleaned = remove_multiple_spaces(test);

    if (cleaned != NULL) {
        printf("Original: '%s'\n", test);
        printf("Cleaned:  '%s'\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}