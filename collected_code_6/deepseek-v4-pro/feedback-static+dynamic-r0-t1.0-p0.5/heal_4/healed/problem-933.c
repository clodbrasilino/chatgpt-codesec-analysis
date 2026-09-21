#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    const char *ptr = input;
    while (input_len < SIZE_MAX / 2 && *ptr != '\0') {
        input_len++;
        ptr++;
    }
    
    if (input_len >= SIZE_MAX / 2) {
        return NULL;
    }

    if (input_len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t max_result_len = input_len * 2 + 1;
    char *result = malloc(max_result_len);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;
    int prev_lower = 0;
    int prev_digit = 0;

    for (size_t i = 0; i < input_len; i++) {
        char c = input[i];
        int curr_upper = (c >= 'A' && c <= 'Z');
        int curr_lower = (c >= 'a' && c <= 'z');
        int curr_digit = (c >= '0' && c <= '9');

        if (i > 0 && curr_upper && (prev_lower || prev_digit)) {
            if (dst_pos >= max_result_len - 1) {
                free(result);
                return NULL;
            }
            result[dst_pos++] = '_';
        }

        if (dst_pos >= max_result_len - 1) {
            free(result);
            return NULL;
        }

        if (curr_upper) {
            result[dst_pos++] = (char)(c + ('a' - 'A'));
        } else {
            result[dst_pos++] = c;
        }

        prev_lower = curr_lower;
        prev_digit = curr_digit;
    }

    result[dst_pos] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCase",
        "thisIsATest",
        "already_snake",
        "with123Numbers",
        "HTMLElement",
        "",
        "a",
        "ABC",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> (conversion failed)\n", test_cases[i]);
        }
    }

    return 0;
}