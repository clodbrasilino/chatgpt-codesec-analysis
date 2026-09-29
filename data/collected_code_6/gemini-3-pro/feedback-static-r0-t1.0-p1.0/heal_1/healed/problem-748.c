#include <stdio.h>
#include <stdlib.h>

char* add_spaces_before_capitals(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    size_t new_str_len = 0;

    while (input[input_len] != '\0') {
        if (input_len > 0 && input[input_len] >= 'A' && input[input_len] <= 'Z') {
            new_str_len++;
        }
        input_len++;
        new_str_len++;
    }

    if (input_len == 0) {
        char* empty_result = (char*)malloc(1);
        if (empty_result != NULL) {
            empty_result[0] = '\0';
        }
        return empty_result;
    }

    char* result = (char*)malloc(new_str_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    result[j++] = input[0];

    for (size_t i = 1; i < input_len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            result[j++] = ' ';
        }
        result[j++] = input[i];
    }
    
    result[j] = '\0';
    return result;
}

int main(void) {
    const char* test_string = "HelloWorldThisIsCTesting";
    char* spaced_string = add_spaces_before_capitals(test_string);

    if (spaced_string != NULL) {
        printf("%s\n", spaced_string);
        free(spaced_string);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}