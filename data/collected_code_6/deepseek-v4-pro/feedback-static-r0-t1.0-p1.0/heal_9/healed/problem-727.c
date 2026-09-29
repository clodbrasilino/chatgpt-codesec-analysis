#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len == 0) {
        char *empty_result = (char *)malloc(1);
        if (empty_result != NULL) {
            empty_result[0] = '\0';
        }
        return empty_result;
    }

    size_t max_result_size = input_len + 1;
    char *result = (char *)malloc(max_result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    
    for (size_t i = 0; i < input_len; i++) {
        char c = input[i];
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9')) {
            if (result_index >= max_result_size - 1) {
                free(result);
                return NULL;
            }
            result[result_index] = c;
            result_index++;
        }
    }

    result[result_index] = '\0';

    char *final_result = (char *)realloc(result, result_index + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_string = "Hello, World! 123...";
    char *cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("%s\n", cleaned);
        free(cleaned);
    }

    return 0;
}