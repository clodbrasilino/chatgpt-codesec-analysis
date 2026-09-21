#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *add_spaces(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

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

    char *result = malloc(len * 2 + 2);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t res_idx = 0;
    size_t start = 0;
    regmatch_t pmatch[3];

    while (start < len) {
        const char *search_str = str + start;
        size_t search_len = len - start;

        if (regexec(&regex, search_str, 3, pmatch, 0) == REG_NOMATCH) {
            memcpy(result + res_idx, search_str, search_len);
            res_idx += search_len;
            break;
        }

        if (pmatch[0].rm_so == -1) {
            break;
        }

        for (size_t i = 0; i < (size_t)pmatch[0].rm_so; i++) {
            result[res_idx++] = search_str[i];
        }

        result[res_idx++] = search_str[pmatch[1].rm_so];
        result[res_idx++] = ' ';
        result[res_idx++] = search_str[pmatch[2].rm_so];

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
    size_t input_len = strlen(input);
    char *output = add_spaces(input, input_len);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}