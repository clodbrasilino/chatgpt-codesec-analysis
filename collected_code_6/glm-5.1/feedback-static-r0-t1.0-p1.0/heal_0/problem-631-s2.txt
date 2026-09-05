#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *swap_whitespace_underscore(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    regmatch_t match;
    size_t src_idx = 0;
    size_t dst_idx = 0;

    while (src_idx < len) {
        if (regexec(&regex, input + src_idx, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                memcpy(result + dst_idx, input + src_idx, match.rm_so);
                dst_idx += match.rm_so;
            }

            char original_char = input[src_idx + match.rm_so];
            if (original_char == ' ') {
                result[dst_idx++] = '_';
            } else {
                result[dst_idx++] = ' ';
            }

            src_idx += match.rm_eo;
        } else {
            size_t remaining = len - src_idx;
            memcpy(result + dst_idx, input + src_idx, remaining);
            dst_idx += remaining;
            src_idx += remaining;
        }
    }

    result[dst_idx] = '\0';
    regfree(&regex);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *processed = swap_whitespace_underscore(argv[1]);
    if (processed == NULL) {
        fprintf(stderr, "Memory allocation or regex error\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", processed);
    free(processed);

    return EXIT_SUCCESS;
}