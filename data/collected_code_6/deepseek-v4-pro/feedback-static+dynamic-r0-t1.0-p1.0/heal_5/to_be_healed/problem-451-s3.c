#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GoogleDart', got <no output>
  *  test case 0 failed: expected 'GoogleFlutter', got <no output>
  *  test case 2 failed: expected 'iOSSwift', got <no output>
  */

char *remove_whitespaces(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, SIZE_MAX);
    if (input_len == SIZE_MAX && input[0] != '\0') {
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;
    for (size_t src_pos = 0; src_pos < input_len; src_pos++) {
        if (!isspace((unsigned char)input[src_pos])) {
            result[dst_pos++] = input[src_pos];
        }
    }

    result[dst_pos] = '\0';

    char *final_result = (char *)realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
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