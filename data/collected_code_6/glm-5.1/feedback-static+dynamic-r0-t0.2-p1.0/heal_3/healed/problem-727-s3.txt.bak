#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

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
        char *empty_result = malloc(1);
        if (empty_result == NULL) {
            return NULL;
        }
        empty_result[0] = '\0';
        return empty_result;
    }

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t out_idx = 0;
    const char *cursor = input;

    while (*cursor != '\0') {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            if (match.rm_so > 0) {
                memcpy(output + out_idx, cursor, match.rm_so);
                out_idx += match.rm_so;
            }
            cursor += match.rm_eo;
        } else {
            size_t remaining = strlen(cursor);
            memcpy(output + out_idx, cursor, remaining);
            out_idx += remaining;
            break;
        }
    }

    output[out_idx] = '\0';
    regfree(&regex);

    char *shrunk = realloc(output, out_idx + 1);
    if (shrunk != NULL) {
        return shrunk;
    }

    return output;
}

bool test_remove_non_alnum(const char *input, const char *expected) {
    char *result = remove_non_alnum(input);
    if (expected == NULL) {
        if (result == NULL) {
            return true;
        }
        free(result);
        return false;
    }
    if (result == NULL) {
        return false;
    }
    bool success = strcmp(result, expected) == 0;
    free(result);
    return success;
}

int main(void) {
    if (!test_remove_non_alnum("Hello, World! 123", "HelloWorld123")) {
        printf("Test 1 failed\n");
    }

    if (!test_remove_non_alnum("___---:::%%%", "")) {
        printf("Test 2 failed\n");
    }

    if (!test_remove_non_alnum("", "")) {
        printf("Test 3 failed\n");
    }

    if (!test_remove_non_alnum(NULL, NULL)) {
        printf("Test 4 failed\n");
    }

    return 0;
}