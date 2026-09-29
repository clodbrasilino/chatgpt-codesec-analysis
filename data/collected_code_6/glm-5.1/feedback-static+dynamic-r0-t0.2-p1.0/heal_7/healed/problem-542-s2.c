#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        char* empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_result_len = (2 * len) + 1;
    char* result = malloc(max_result_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t r_idx = 0;
    const char* p = str;

    while (1) {
        regmatch_t match;
        int match_ret = regexec(&regex, p, 1, &match, 0);
        
        if (match_ret == REG_NOMATCH) {
            size_t remaining_len = strlen(p);
            if (r_idx + remaining_len >= max_result_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (remaining_len > 0) {
                memcpy(result + r_idx, p, remaining_len);
            }
            r_idx += remaining_len;
            break;
        }
        
        if (match_ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_len = match.rm_so;

        if (r_idx + match_len + 1 >= max_result_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match_len > 0) {
            memcpy(result + r_idx, p, match_len);
            r_idx += match_len;
        }
        
        result[r_idx] = ':';
        r_idx++;

        p += match.rm_eo;
    }

    if (r_idx >= max_result_len) {
        r_idx = max_result_len - 1;
    }
    result[r_idx] = '\0';

    char* shrunk = realloc(result, r_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    regfree(&regex);
    return result;
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char* replaced = replace_with_colon(argv[1]);
    if (replaced == NULL) {
        fprintf(stderr, "Error: Memory allocation or regex compilation failed\n");
        return 1;
    }

    printf("%s\n", replaced);
    free(replaced);
    return 0;
}