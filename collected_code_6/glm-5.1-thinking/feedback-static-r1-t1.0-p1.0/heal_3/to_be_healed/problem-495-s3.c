#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_lowercase_substrings(const char *str) {
    if (!str) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        regfree(&regex);
        return NULL;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *p = str;
    size_t out_idx = 0;
    regmatch_t match;

    while (p <= str + len) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = str + len - p;
            size_t available = len - out_idx;
            size_t copy_len = remaining_len < available ? remaining_len : available;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out_idx, p, copy_len);
            out_idx += copy_len;
            break;
        }

        if (match.rm_so > 0) {
            size_t available = len - out_idx;
            size_t copy_len = (size_t)match.rm_so < available ? (size_t)match.rm_so : available;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out_idx, p, copy_len);
            out_idx += copy_len;
        }

        p += match.rm_eo;
        if (match.rm_eo == 0) {
            if (*p) {
                p++;
            } else {
                break;
            }
        }
    }

    result[out_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, out_idx + 1);
    return shrunk != NULL ? shrunk : result;
}

int main(void) {
    const char *input = "HelloWorldABCdefGHI";
    char *output = remove_lowercase_substrings(input);
    
    if (output != NULL) {
        printf("Original: %s\nResult: %s\n", input, output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation or regex compilation failed\n");
        return 1;
    }
    
    return 0;
}