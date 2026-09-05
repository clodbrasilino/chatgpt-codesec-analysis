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
    int ret = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_offset = 0;
    size_t dest_offset = 0;

    while (src_offset < len) {
        int exec_ret = regexec(&regex, str + src_offset, 1, &match, 0);
        if (exec_ret != 0) {
            size_t remaining = len - src_offset;
            if (dest_offset + remaining >= max_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dest_offset, str + src_offset, remaining);
            dest_offset += remaining;
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t before_match = (size_t)match.rm_so;
        size_t match_len = (size_t)(match.rm_eo - match.rm_so);

        if (dest_offset + before_match + 1 + match_len >= max_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (before_match > 0) {
            memcpy(result + dest_offset, str + src_offset, before_match);
            dest_offset += before_match;
        }

        if (src_offset > 0 || before_match > 0) {
            result[dest_offset++] = ' ';
        }

        memcpy(result + dest_offset, str + src_offset + before_match, match_len);
        dest_offset += match_len;

        src_offset += before_match + match_len;
    }

    if (dest_offset >= max_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[dest_offset] = '\0';

    regfree(&regex);

    char *shrunk = realloc(result, dest_offset + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *result1 = add_spaces("HelloWorld");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = add_spaces("ThisIsATest");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = add_spaces("NoSpaces");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = add_spaces("already spaced");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    char *result5 = add_spaces("");
    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }

    char *result6 = add_spaces(NULL);
    if (result6 == NULL) {
        printf("NULL handled\n");
    }

    return 0;
}