#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < input_len && regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            memcpy(result + dst_pos, input + src_pos, match_start - src_pos);
            dst_pos += match_start - src_pos;
        }

        src_pos = match_end;

        if (match.rm_eo == match.rm_so) {
            if (src_pos < input_len) {
                result[dst_pos++] = input[src_pos++];
            } else {
                break;
            }
        }
    }

    if (src_pos < input_len) {
        memcpy(result + dst_pos, input + src_pos, input_len - src_pos);
        dst_pos += input_len - src_pos;
    }

    result[dst_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "HelloWorld123abcXYZdef456";
    char *cleaned = remove_lowercase_substrings(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned:  %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}