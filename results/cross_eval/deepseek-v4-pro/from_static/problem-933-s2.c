#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <errno.h>

#define MAX_INPUT_LENGTH (1024 * 1024)

static char *checked_strdup(const char *str, size_t len) {
    char *copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    if (len > 0) {
        memmove(copy, str, len);
    }
    copy[len] = '\0';
    return copy;
}

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    size_t input_len = 0;
    const char *p = input;
    const char *max_ptr = input + MAX_INPUT_LENGTH;
    while (p < max_ptr && *p != '\0') {
        p++;
        input_len++;
    }
    if (*p != '\0') {
        errno = EINVAL;
        return NULL;
    }

    if (input_len == 0) {
        char *empty_result = (char *)malloc(1);
        if (empty_result == NULL) {
            return NULL;
        }
        empty_result[0] = '\0';
        return empty_result;
    }

    regex_t regex;
    const char *pattern = "([a-z0-9])([A-Z])";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        errno = EINVAL;
        return NULL;
    }

    size_t max_output_len = input_len * 2 + 1;
    char *result = (char *)malloc(max_output_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_offset = 0;
    size_t dst_pos = 0;
    int found = 0;

    while (src_offset < input_len) {
        regmatch_t matches[3];
        int match_result = regexec(&regex, input + src_offset, 3, matches, 0);
        if (match_result != 0) {
            break;
        }

        size_t match_start = (size_t)matches[0].rm_so;
        size_t match_end = (size_t)matches[0].rm_eo;
        size_t first_end = (size_t)matches[1].rm_eo;
        size_t second_start = (size_t)matches[2].rm_so;

        if (match_start < match_end && match_end <= input_len - src_offset) {
            if (match_start > 0) {
                size_t copy_len = match_start;
                if (dst_pos + copy_len >= max_output_len) {
                    free(result);
                    regfree(&regex);
                    errno = ENOSPC;
                    return NULL;
                }
                memmove(result + dst_pos, input + src_offset, copy_len);
                dst_pos += copy_len;
            }

            if (dst_pos + 2 >= max_output_len) {
                free(result);
                regfree(&regex);
                errno = ENOSPC;
                return NULL;
            }

            size_t first_char_idx = src_offset + first_end - 1;
            if (first_char_idx >= input_len) {
                free(result);
                regfree(&regex);
                errno = EINVAL;
                return NULL;
            }
            result[dst_pos++] = input[first_char_idx];

            result[dst_pos++] = '_';

            size_t second_char_idx = src_offset + second_start;
            if (second_char_idx >= input_len) {
                free(result);
                regfree(&regex);
                errno = EINVAL;
                return NULL;
            }
            result[dst_pos++] = (char)tolower((unsigned char)input[second_char_idx]);

            src_offset += match_end;
            found = 1;
        } else {
            break;
        }
    }

    if (src_offset < input_len) {
        size_t remaining = input_len - src_offset;
        if (dst_pos + remaining >= max_output_len) {
            free(result);
            regfree(&regex);
            errno = ENOSPC;
            return NULL;
        }
        memmove(result + dst_pos, input + src_offset, remaining);
        dst_pos += remaining;
    }

    if (dst_pos >= max_output_len) {
        free(result);
        regfree(&regex);
        errno = ENOSPC;
        return NULL;
    }
    result[dst_pos] = '\0';
    regfree(&regex);

    if (!found) {
        char *copy = checked_strdup(input, input_len);
        if (copy == NULL) {
            free(result);
            return NULL;
        }
        free(result);
        result = copy;
        dst_pos = input_len;
    }

    char *final_result = (char *)realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_strings[] = {
        "camelCase",
        "snake_case",
        "myVariableName",
        "HTTPResponseCode",
        "test123Case",
        "already_snake",
        "A",
        "",
        "ABC",
        "convertJSONToXML"
    };

    size_t test_count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < test_count; i++) {
        char *converted = camel_to_snake(test_strings[i]);
        if (converted != NULL) {
            printf("\"%s\" -> \"%s\"\n", test_strings[i], converted);
            free(converted);
        } else {
            printf("\"%s\" -> conversion failed\n", test_strings[i]);
        }
    }

    return 0;
}