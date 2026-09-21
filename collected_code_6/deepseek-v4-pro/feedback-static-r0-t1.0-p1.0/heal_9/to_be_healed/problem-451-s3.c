#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char *allocate_empty_string(void) {
    char *empty_result = (char *)malloc(1);
    if (empty_result != NULL) {
        empty_result[0] = '\0';
    }
    return empty_result;
}

static int safe_copy(char *dst, size_t *dst_pos, const char *src, size_t copy_len, size_t dst_capacity) {
    if (*dst_pos + copy_len > dst_capacity) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst + *dst_pos, src, copy_len);
    *dst_pos += copy_len;
    return 1;
}

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX / 2);

    if (input_len == 0) {
        return allocate_empty_string();
    }

    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t buffer_size = input_len + 1;
    char *result = (char *)malloc(buffer_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < input_len && regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
        size_t match_start = src_pos + match.rm_so;
        size_t match_end = src_pos + match.rm_eo;

        if (match_start > src_pos) {
            size_t copy_len = match_start - src_pos;
            if (!safe_copy(result, &dst_pos, input + src_pos, copy_len, input_len)) {
                free(result);
                regfree(&regex);
                return NULL;
            }
        }

        src_pos = match_end;

        if (match.rm_so == match.rm_eo) {
            if (src_pos < input_len) {
                if (dst_pos >= input_len) {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result[dst_pos++] = input[src_pos++];
            } else {
                break;
            }
        }
    }

    if (src_pos < input_len) {
        size_t copy_len = input_len - src_pos;
        if (!safe_copy(result, &dst_pos, input + src_pos, copy_len, input_len)) {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    if (dst_pos > input_len) {
        free(result);
        regfree(&regex);
        return NULL;
    }

    result[dst_pos] = '\0';
    regfree(&regex);

    char *final_result = (char *)realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "Hello   World\t\n  from C!";
    char *cleaned = remove_whitespaces(test_string);

    if (cleaned == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Original: '%s'\n", test_string);
    printf("Cleaned:  '%s'\n", cleaned);

    free(cleaned);
    return EXIT_SUCCESS;
}