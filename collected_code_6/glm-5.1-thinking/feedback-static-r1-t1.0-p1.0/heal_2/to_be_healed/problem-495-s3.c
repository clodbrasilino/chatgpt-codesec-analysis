#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *str) {
    regex_t regex;
    int ret = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *p = str;
    size_t out_idx = 0;
    size_t remaining_len = len;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            if (out_idx + remaining_len <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + out_idx, p, remaining_len);
                out_idx += remaining_len;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (out_idx + match.rm_so <= len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + out_idx, p, match.rm_so);
                out_idx += match.rm_so;
            }
        }

        p += match.rm_eo;
        remaining_len -= match.rm_eo;
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