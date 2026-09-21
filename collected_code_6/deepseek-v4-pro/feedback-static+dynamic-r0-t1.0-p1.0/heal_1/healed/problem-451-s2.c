#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, ((size_t)-1) - 1);
    if (input_len == ((size_t)-1) - 1) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    regmatch_t match;

    while (src_pos < input_len) {
        if (regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
            if (match.rm_so > 0) {
                if (dst_pos + match.rm_so > input_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(result + dst_pos, input + src_pos, match.rm_so);
                dst_pos += match.rm_so;
            }
            if (src_pos + match.rm_eo < src_pos) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            src_pos += match.rm_eo;
        } else {
            size_t remaining = input_len - src_pos;
            if (dst_pos + remaining > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + dst_pos, input + src_pos, remaining);
            dst_pos += remaining;
            break;
        }
    }

    result[dst_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "Hello   World\tfrom\nC programming";
    char *cleaned = remove_whitespaces(test_string);
    
    if (cleaned != NULL) {
        printf("Original: '%s'\n", test_string);
        printf("Cleaned:  '%s'\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}