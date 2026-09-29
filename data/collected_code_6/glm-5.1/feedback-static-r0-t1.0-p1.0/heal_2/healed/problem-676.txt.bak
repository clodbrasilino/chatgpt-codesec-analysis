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
    char *result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_idx = 0;
    const char *search_start = input;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, search_start, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining_len = strlen(search_start);
            memcpy(result + result_idx, search_start, remaining_len);
            result_idx += remaining_len;
            break;
        }

        if (ret != 0) {
            break;
        }

        memcpy(result + result_idx, search_start, match.rm_so);
        result_idx += match.rm_so;

        search_start += match.rm_eo;
    }

    result[result_idx] = '\0';

    if (result_idx + 1 < input_len + 1) {
        char *trimmed_result = realloc(result, result_idx + 1);
        if (trimmed_result != NULL) {
            result = trimmed_result;
        }
    }

    regfree(&regex);

    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *cleaned = remove_non_alnum(argv[1]);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return 1;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    return 0;
}