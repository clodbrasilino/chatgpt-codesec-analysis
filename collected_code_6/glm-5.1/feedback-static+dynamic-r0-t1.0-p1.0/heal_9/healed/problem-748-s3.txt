#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *put_spaces(const char *str) {
    if (!str) return NULL;

    regex_t regex;
    regmatch_t match;
    int err;
    size_t str_len = strnlen(str, 1024 * 1024);
    size_t capacity = (str_len * 2) + 1;
    char *result = malloc(capacity);
    if (!result) return NULL;

    size_t result_len = 0;

    err = regcomp(&regex, "[A-Z][a-z]*", REG_EXTENDED);
    if (err != 0) {
        free(result);
        return NULL;
    }

    const char *p = str;
    const char *str_end = str + str_len;

    while (p < str_end) {
        err = regexec(&regex, p, 1, &match, 0);
        if (err == REG_NOMATCH) break;
        if (err != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        if (match.rm_so == -1) break;

        size_t prefix_len = (size_t)match.rm_so;
        size_t match_len = (size_t)(match.rm_eo - match.rm_so);

        if (result_len + prefix_len + match_len + 2 >= capacity) {
            capacity = (result_len + prefix_len + match_len + 2) * 2;
            char *temp = realloc(result, capacity);
            if (!temp) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            result = temp;
        }

        if (prefix_len > 0) {
            size_t available = capacity - result_len;
            size_t copy_len = prefix_len < available ? prefix_len : available;
            memcpy(result + result_len, p, copy_len);
            result_len += copy_len;
        }

        if (result_len > 0 && result[result_len - 1] != ' ') {
            if (result_len + 1 < capacity) {
                result[result_len++] = ' ';
            }
        }

        if (match_len > 0) {
            size_t available = capacity - result_len;
            size_t copy_len = match_len < available ? match_len : available;
            memcpy(result + result_len, p + match.rm_so, copy_len);
            result_len += copy_len;
        }

        p += match.rm_eo;
    }

    size_t remaining_len = (size_t)(str_end - p);
    if (remaining_len > 0) {
        if (result_len + remaining_len + 1 >= capacity) {
            capacity = result_len + remaining_len + 2;
            char *temp = realloc(result, capacity);
            if (!temp) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            result = temp;
        }
        size_t available = capacity - result_len;
        size_t copy_len = remaining_len < available ? remaining_len : available;
        memcpy(result + result_len, p, copy_len);
        result_len += copy_len;
    }

    result[result_len] = '\0';

    regfree(&regex);

    char *final_result = realloc(result, result_len + 1);
    if (!final_result) return result;

    return final_result;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *output = put_spaces(argv[1]);
    if (!output) {
        fprintf(stderr, "Memory or regex error\n");
        return 1;
    }

    printf("%s\n", output);

    free(output);
    return 0;
}