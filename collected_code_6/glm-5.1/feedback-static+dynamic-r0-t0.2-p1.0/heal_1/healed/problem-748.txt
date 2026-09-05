#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([A-Z][a-z]*)", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t max_len = strlen(input) * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char *ptr = input;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, ptr, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            strcpy(result + result_idx, ptr);
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so == -1) {
            strcpy(result + result_idx, ptr);
            break;
        }

        if (result_idx + match.rm_so + 1 >= max_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        strncpy(result + result_idx, ptr, match.rm_so);
        result_idx += match.rm_so;

        if (result_idx > 0) {
            result[result_idx++] = ' ';
        }

        if (result_idx + (match.rm_eo - match.rm_so) >= max_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        strncpy(result + result_idx, ptr + match.rm_so, match.rm_eo - match.rm_so);
        result_idx += match.rm_eo - match.rm_so;

        ptr += match.rm_eo;
    }

    regfree(&regex);

    size_t final_len = strlen(result) + 1;
    char *shrunk = realloc(result, final_len);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *res1 = add_spaces("HelloWorldThisIsC");
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    char *res2 = add_spaces("NoSpaces");
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    char *res3 = add_spaces("already spaced");
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    const char *res4 = add_spaces(NULL);
    if (res4 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}