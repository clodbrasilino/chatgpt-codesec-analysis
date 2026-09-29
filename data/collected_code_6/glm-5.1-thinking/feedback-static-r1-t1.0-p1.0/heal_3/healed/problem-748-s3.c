#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    size_t safe_len = strnlen(str, len);

    if (safe_len == 0) {
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

    size_t max_res_len = safe_len * 2 + 2;
    char *result = malloc(max_res_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    size_t start = 0;
    regmatch_t pmatch[3];

    while (start < safe_len) {
        const char *search_str = str + start;
        size_t search_len = safe_len - start;

        if (regexec(&regex, search_str, 3, pmatch, 0) == REG_NOMATCH) {
            size_t remaining = max_res_len - res_idx - 1;
            size_t copy_len = search_len < remaining ? search_len : remaining;
            memcpy(result + res_idx, search_str, copy_len);
            res_idx += copy_len;
            break;
        }

        if (pmatch[0].rm_so == -1) {
            break;
        }

        size_t prefix_len = (size_t)pmatch[0].rm_so;
        size_t remaining = max_res_len - res_idx - 1;
        size_t prefix_copy_len = prefix_len < remaining ? prefix_len : remaining;
        memcpy(result + res_idx, search_str, prefix_copy_len);
        res_idx += prefix_copy_len;

        if (res_idx < max_res_len - 1) {
            result[res_idx++] = search_str[pmatch[1].rm_so];
        }
        if (res_idx < max_res_len - 1) {
            result[res_idx++] = ' ';
        }
        if (res_idx < max_res_len - 1) {
            result[res_idx++] = search_str[pmatch[2].rm_so];
        }

        start += pmatch[0].rm_eo;
    }

    result[res_idx] = '\0';

    regfree(&regex);

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *input = "HelloWorldThisIsATest";
    size_t input_len = strnlen(input, 4096);
    char *output = add_spaces(input, input_len);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}