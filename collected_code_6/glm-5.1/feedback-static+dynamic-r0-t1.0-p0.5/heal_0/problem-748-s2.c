#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t r_idx = 0;
    const char *p = str;
    regmatch_t match[2];

    while (1) {
        ret = regexec(&regex, p, 2, match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(p);
            if (r_idx + remaining >= max_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            strcpy(result + r_idx, p);
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match[1].rm_so == -1) {
            size_t remaining = strlen(p);
            if (r_idx + remaining >= max_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            strcpy(result + r_idx, p);
            break;
        }

        size_t prefix_len = match[1].rm_so;
        size_t word_len = match[1].rm_eo - match[1].rm_so;

        if (r_idx + prefix_len + word_len + 2 >= max_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (prefix_len > 0) {
            memcpy(result + r_idx, p, prefix_len);
            r_idx += prefix_len;
        }

        if (r_idx > 0 && result[r_idx - 1] != ' ') {
            result[r_idx++] = ' ';
        }

        memcpy(result + r_idx, p + match[1].rm_so, word_len);
        r_idx += word_len;

        p += match[1].rm_eo;
        if (*p == '\0') {
            result[r_idx] = '\0';
            break;
        }
    }

    regfree(&regex);

    char *final_result = realloc(result, r_idx + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    char *result = add_spaces("HelloWorldFromCProgramming");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = add_spaces("NoSpaces");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = add_spaces("already has spaces");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = add_spaces("MixedCASEWord");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = add_spaces("");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}