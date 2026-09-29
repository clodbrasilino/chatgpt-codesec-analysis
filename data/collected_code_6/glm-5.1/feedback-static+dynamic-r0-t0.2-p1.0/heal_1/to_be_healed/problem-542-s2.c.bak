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

    size_t max_matches = len;
    regmatch_t* matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    char* result = malloc(len + 1);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    size_t r_idx = 0;
    const char* p = str;

    while (1) {
        int match_ret = regexec(&regex, p, 1, matches, 0);
        if (match_ret == REG_NOMATCH) {
            strcpy(result + r_idx, p);
            break;
        }
        if (match_ret != 0) {
            free(result);
            free(matches);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = matches[0].rm_so;
        size_t match_len = match_start;

        memcpy(result + r_idx, p, match_len);
        r_idx += match_len;
        result[r_idx] = ':';
        r_idx++;

        p += matches[0].rm_eo;
    }

    free(matches);
    regfree(&regex);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
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