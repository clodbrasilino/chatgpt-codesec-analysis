#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    regmatch_t match;
    char *cursor = (char *)input;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            memcpy(result + result_index, cursor, match_start);
            result_index += match_start;
        }

        cursor += match_end;
        if (match_end == 0) {
            cursor++;
        }
    }

    strcpy(result + result_index, cursor);
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123";
    char *cleaned = remove_non_alphanumeric(test_string);

    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }

    return 0;
}