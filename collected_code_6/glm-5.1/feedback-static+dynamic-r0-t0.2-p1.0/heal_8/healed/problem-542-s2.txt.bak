#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
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

    regmatch_t match;

    size_t alloc_len = len + 1;
    char* result = malloc(alloc_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t r_idx = 0;
    const char* p = str;

    while (1) {
        int match_ret = regexec(&regex, p, 1, &match, 0);
        if (match_ret == REG_NOMATCH) {
            size_t remaining = strlen(p);
            if (r_idx + remaining + 1 > alloc_len) {
                alloc_len = r_idx + remaining + 1;
                char* new_result = realloc(result, alloc_len);
                if (new_result == NULL) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = new_result;
            }
            strcpy(result + r_idx, p);
            break;
        }
        if (match_ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = match.rm_so;
        size_t match_len = match_start;

        if (r_idx + match_len + 1 > alloc_len) {
            alloc_len = (r_idx + match_len + 1) * 2;
            char* new_result = realloc(result, alloc_len);
            if (new_result == NULL) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
        }

        memcpy(result + r_idx, p, match_len);
        r_idx += match_len;
        result[r_idx] = ':';
        r_idx++;

        p += match.rm_eo;
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