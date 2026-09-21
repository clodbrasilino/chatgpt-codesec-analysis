#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX) {
        return NULL;
    }

    char *output = malloc(input_len + 1);
    if (output == NULL) {
        return NULL;
    }

    if (input_len == 0) {
        output[0] = '\0';
        return output;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        free(output);
        return NULL;
    }

    size_t out_idx = 0;
    const char *cursor = input;

    while (*cursor != '\0') {
        regmatch_t match;
        int exec_ret = regexec(&regex, cursor, 1, &match, 0);

        if (exec_ret == 0) {
            if (match.rm_so > 0) {
                if (out_idx + match.rm_so <= input_len) {
                    memcpy(output + out_idx, cursor, match.rm_so);
                    out_idx += match.rm_so;
                }
            }
            if (match.rm_eo == 0) {
                cursor++;
            } else {
                cursor += match.rm_eo;
            }
        } else {
            size_t remaining = strlen(cursor);
            if (out_idx + remaining <= input_len) {
                memcpy(output + out_idx, cursor, remaining);
                out_idx += remaining;
            }
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

int main(void) {
    char *result1 = remove_non_alnum("Hello, World! 123");
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *result2 = remove_non_alnum("___---:::%%%");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *result3 = remove_non_alnum("");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char *result4 = remove_non_alnum(NULL);
    if (result4 == NULL) {
        printf("NULL input handled\n");
    } else {
        free(result4);
    }

    return 0;
}