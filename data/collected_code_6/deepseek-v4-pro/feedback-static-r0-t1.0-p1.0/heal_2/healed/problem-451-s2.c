#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    const char *p = input;
    size_t max_len = (size_t)-1;
    while (input_len < max_len && *p != '\0') {
        input_len++;
        p++;
    }
    
    if (*p != '\0') {
        return NULL;
    }
    
    if (input_len == 0) {
        char *empty = (char *)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
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
                size_t copy_len = (size_t)match.rm_so;
                if (dst_pos + copy_len > input_len) {
                    copy_len = input_len - dst_pos;
                }
                if (dst_pos + copy_len <= input_len) {
                    memcpy(result + dst_pos, input + src_pos, copy_len);
                    dst_pos += copy_len;
                }
            }
            size_t advance = (size_t)match.rm_eo;
            if (advance > input_len - src_pos) {
                advance = input_len - src_pos;
            }
            src_pos += advance;
        } else {
            size_t remaining = input_len - src_pos;
            if (dst_pos + remaining > input_len) {
                remaining = input_len - dst_pos;
            }
            if (dst_pos + remaining <= input_len) {
                memcpy(result + dst_pos, input + src_pos, remaining);
                dst_pos += remaining;
            }
            break;
        }
    }

    if (dst_pos <= input_len) {
        result[dst_pos] = '\0';
    } else {
        result[input_len] = '\0';
        dst_pos = input_len;
    }
    
    regfree(&regex);

    char *final_result = (char *)realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
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