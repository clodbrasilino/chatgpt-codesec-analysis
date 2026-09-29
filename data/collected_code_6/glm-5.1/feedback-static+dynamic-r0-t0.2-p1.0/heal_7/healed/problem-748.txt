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

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    size_t max_len = input_len * 2 + 1;
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
            snprintf(result + result_idx, max_len - result_idx, "%s", ptr);
            break;
        }

        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so == -1) {
            snprintf(result + result_idx, max_len - result_idx, "%s", ptr);
            break;
        }

        if (result_idx + match.rm_so + 1 >= max_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        snprintf(result + result_idx, match.rm_so + 1, "%s", ptr);
        result_idx += match.rm_so;

        if (result_idx > 0) {
            result[result_idx++] = ' ';
        }

        if (result_idx + (match.rm_eo - match.rm_so) >= max_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        snprintf(result + result_idx, (match.rm_eo - match.rm_so) + 1, "%s", ptr + match.rm_so);
        result_idx += match.rm_eo - match.rm_so;

        ptr += match.rm_eo;
    }

    regfree(&regex);

    size_t final_len = 0;
    while (result[final_len] != '\0') {
        final_len++;
    }

    char *shrunk = realloc(result, final_len + 1);
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

    char *res4 = add_spaces(NULL);
    if (res4 == NULL) {
        printf("NULL input handled\n");
    } else {
        free(res4);
    }

    return 0;
}