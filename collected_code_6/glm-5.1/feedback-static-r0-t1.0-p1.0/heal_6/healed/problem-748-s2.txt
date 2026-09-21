#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces_capitals(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t cap = len * 2 + 2;
    char *result = malloc(cap);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED);
    if (reti != 0) {
        free(result);
        return NULL;
    }

    size_t res_idx = 0;
    const char *p = str;

    while (*p) {
        regmatch_t match;
        reti = regexec(&regex, p, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            size_t remaining_len = strlen(p);
            size_t available = cap - res_idx;
            size_t copy_len = remaining_len < available ? remaining_len : available;
            if (copy_len > 0) {
                if (res_idx <= cap && copy_len <= remaining_len) {
                    memcpy(result + res_idx, p, copy_len);
                }
                res_idx += copy_len;
            }
            break;
        } else if (reti != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        } else {
            if (match.rm_so > 0) {
                size_t copy_len = (size_t)match.rm_so;
                size_t available = cap - res_idx;
                if (copy_len > available) {
                    copy_len = available;
                }
                if (copy_len > 0) {
                    memcpy(result + res_idx, p, copy_len);
                    res_idx += copy_len;
                }
            }
            if (p != str && res_idx > 0) {
                if (res_idx < cap - 1) {
                    result[res_idx++] = ' ';
                }
            }
            size_t match_len = match.rm_eo - match.rm_so;
            size_t available = cap - res_idx;
            if (match_len > available) {
                match_len = available;
            }
            if (match_len > 0) {
                memcpy(result + res_idx, p + match.rm_so, match_len);
                res_idx += match_len;
            }
            p += match.rm_eo;
        }
    }

    if (res_idx < cap) {
        result[res_idx] = '\0';
    } else {
        result[cap - 1] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *res = add_spaces_capitals(argv[1]);
    if (res == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", res);
    free(res);

    return 0;
}