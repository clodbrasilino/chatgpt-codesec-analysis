#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len == 0) {
        regfree(&regex);
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_matches = input_len;
    regmatch_t *matches = malloc(max_matches * sizeof(regmatch_t));
    if (matches == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_size = input_len + 1;
    char *result = malloc(result_size);
    if (result == NULL) {
        free(matches);
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    size_t search_start = 0;

    while (search_start < input_len) {
        int exec_ret = regexec(&regex, input + search_start, 1, matches, 0);
        if (exec_ret == REG_NOMATCH) {
            size_t remaining_len = input_len - search_start;
            memcpy(result + result_idx, input + search_start, remaining_len);
            result_idx += remaining_len;
            break;
        } else if (exec_ret != 0) {
            free(result);
            free(matches);
            regfree(&regex);
            return NULL;
        }

        if (matches[0].rm_so == -1) {
            break;
        }

        size_t match_start = search_start + matches[0].rm_so;
        size_t match_end = search_start + matches[0].rm_eo;

        size_t copy_len = match_start - search_start;
        if (copy_len > 0) {
            memcpy(result + result_idx, input + search_start, copy_len);
            result_idx += copy_len;
        }

        search_start = match_end;
    }

    result[result_idx] = '\0';

    char *trimmed_result = realloc(result, result_idx + 1);
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    free(matches);
    regfree(&regex);

    return result;
}

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___test___");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *already_freed = remove_non_alnum("Test");
    if (already_freed != NULL) {
        printf("%s\n", already_freed);
        free(already_freed);
    }

    char *result4 = remove_non_alnum(NULL);

    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    } else {
        printf("(null)\n");
    }

    return 0;
}