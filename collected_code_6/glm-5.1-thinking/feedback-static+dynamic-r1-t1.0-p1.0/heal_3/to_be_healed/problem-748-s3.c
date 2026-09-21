#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        char *res = malloc(1);
        if (res) {
            res[0] = '\0';
        }
        return res;
    }

    regex_t regex;
    if (regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t result_size = len * 2 + 2;
    char *result = malloc(result_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    size_t start = 0;
    regmatch_t pmatch[3];

    while (start < len) {
        const char *search_str = str + start;
        if (regexec(&regex, search_str, 3, pmatch, 0) == REG_NOMATCH) {
            size_t remaining = len - start;
            if (res_idx + remaining < result_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, search_str, remaining);
                res_idx += remaining;
            }
            break;
        }

        if (pmatch[0].rm_so == -1) {
            break;
        }

        for (size_t i = 0; i < (size_t)pmatch[0].rm_so; i++) {
            if (res_idx < result_size - 1) {
                result[res_idx++] = search_str[i];
            }
        }

        if (res_idx < result_size - 1) {
            result[res_idx++] = search_str[pmatch[1].rm_so];
        }
        if (res_idx < result_size - 1) {
            result[res_idx++] = ' ';
        }
        if (res_idx < result_size - 1) {
            result[res_idx++] = search_str[pmatch[2].rm_so];
        }

        start += pmatch[0].rm_eo;
    }

    if (res_idx < result_size) {
        result[res_idx] = '\0';
    } else {
        result[result_size - 1] = '\0';
    }

    regfree(&regex);

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *input = "HelloWorldThisIsATest";
    char *output = add_spaces(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}