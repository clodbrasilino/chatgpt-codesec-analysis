#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>
#include <ctype.h>

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static void safe_memcpy(char *dest, size_t dest_size, size_t *dest_pos,
                        const char *src, size_t src_len) {
    if (dest == NULL || src == NULL || src_len == 0) {
        return;
    }
    size_t available = dest_size - *dest_pos;
    size_t copy_len = (src_len < available) ? src_len : available;
    if (copy_len > 0) {
        memcpy(dest + *dest_pos, src, copy_len);
        *dest_pos += copy_len;
    }
}

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    const char *ptr = input;
    while (*ptr != '\0') {
        input_len++;
        ptr++;
    }
    
    if (input_len == 0) {
        char *empty = (char *)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    regex_t regex;
    const char *pattern = "([a-z0-9])([A-Z])";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_output_len = input_len * 2 + 1;
    if (max_output_len < input_len) {
        regfree(&regex);
        return NULL;
    }
    
    char *result = (char *)malloc(max_output_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    const char *remaining = input;
    regmatch_t matches[3];

    while (src_pos < input_len && regexec(&regex, remaining, 3, matches, 0) == 0) {
        size_t match_start = matches[0].rm_so;
        size_t match_end = matches[0].rm_eo;
        size_t group1_start = matches[1].rm_so;
        size_t group1_end = matches[1].rm_eo;
        size_t group2_start = matches[2].rm_so;
        size_t group2_end = matches[2].rm_eo;

        if (match_start > 0) {
            safe_memcpy(result, max_output_len, &dst_pos, remaining, match_start);
        }

        if (group1_start != (size_t)-1 && group1_end != (size_t)-1) {
            size_t group1_len = group1_end - group1_start;
            safe_memcpy(result, max_output_len, &dst_pos, remaining + group1_start, group1_len);
        }

        if (dst_pos < max_output_len) {
            result[dst_pos++] = '_';
        }

        if (group2_start != (size_t)-1 && group2_end != (size_t)-1 && dst_pos < max_output_len) {
            char lower_char = remaining[group2_start];
            if (lower_char >= 'A' && lower_char <= 'Z') {
                lower_char = tolower(lower_char);
            }
            result[dst_pos++] = lower_char;
        }

        src_pos += match_end;
        remaining += match_end;
    }

    if (src_pos < input_len) {
        size_t remaining_len = input_len - src_pos;
        safe_memcpy(result, max_output_len, &dst_pos, remaining, remaining_len);
    }

    if (dst_pos < max_output_len) {
        result[dst_pos] = '\0';
    } else {
        result[max_output_len - 1] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCaseString",
        "simple",
        "already_snake_case",
        "with123Numbers",
        "HTTPResponseCode",
        "a",
        "",
        "ABC",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("%s\n", converted);
            free(converted);
        }
    }

    return 0;
}