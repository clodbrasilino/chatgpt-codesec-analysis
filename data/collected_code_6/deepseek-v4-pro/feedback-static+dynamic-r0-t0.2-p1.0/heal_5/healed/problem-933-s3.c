#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static int safe_memcpy(char *dest, size_t dest_size, size_t *dest_pos,
                        const char *src, size_t src_len) {
    if (dest == NULL || src == NULL || src_len == 0) {
        return 0;
    }
    if (*dest_pos >= dest_size) {
        return -1;
    }
    size_t available = dest_size - *dest_pos;
    size_t copy_len = (src_len < available) ? src_len : available;
    if (copy_len > 0) {
        memmove(dest + *dest_pos, src, copy_len);
        *dest_pos += copy_len;
    }
    return (copy_len >= src_len) ? 0 : -1;
}

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    
    if (input_len == 0) {
        char *empty = (char *)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t max_output_len = input_len * 2 + 1;
    if (max_output_len < input_len) {
        return NULL;
    }
    
    char *result = (char *)malloc(max_output_len);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;

    while (src_pos < input_len) {
        if (src_pos > 0 && input[src_pos] >= 'A' && input[src_pos] <= 'Z') {
            char prev_char = input[src_pos - 1];
            int prev_is_lower = (prev_char >= 'a' && prev_char <= 'z');
            int prev_is_digit = (prev_char >= '0' && prev_char <= '9');
            
            if ((prev_is_lower || prev_is_digit) && dst_pos + 1 < max_output_len) {
                result[dst_pos++] = '_';
            }
        }
        
        if (dst_pos < max_output_len) {
            char current = input[src_pos];
            if (current >= 'A' && current <= 'Z') {
                current = (char)tolower((unsigned char)current);
            }
            result[dst_pos++] = current;
        }
        
        src_pos++;
    }

    if (dst_pos < max_output_len) {
        result[dst_pos] = '\0';
    } else {
        result[max_output_len - 1] = '\0';
    }

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