#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (input_len == 0) {
        result[0] = '\0';
        return result;
    }

    size_t dst_pos = 0;
    for (size_t src_pos = 0; src_pos < input_len; src_pos++) {
        if (!isspace((unsigned char)input[src_pos])) {
            result[dst_pos++] = input[src_pos];
        }
    }

    result[dst_pos] = '\0';

    if (dst_pos < input_len) {
        char *final_result = (char *)realloc(result, dst_pos + 1);
        if (final_result != NULL) {
            return final_result;
        }
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "GoogleFlutter",
        "GoogleDart",
        "iOSSwift"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *cleaned = remove_whitespaces(test_cases[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Error processing string\n");
            return EXIT_FAILURE;
        }
        printf("%s\n", cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}