#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_whitespaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* ptr = input;
    while (*ptr != '\0') {
        ptr++;
    }
    size_t input_len = (size_t)(ptr - input);

    if (input_len == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;

    for (size_t i = 0; i < input_len; i++) {
        if (!isspace((unsigned char)input[i])) {
            result[result_index++] = input[i];
        }
    }

    result[result_index] = '\0';

    if (result_index == input_len) {
        return result;
    }

    char* final_result = (char*)realloc(result, result_index + 1);
    if (final_result != NULL) {
        return final_result;
    }

    return result;
}

int main() {
    const char* test_strings[] = {
        "Google Flutter",
        "Google Dart",
        "iOS Swift"
    };
    int num_strings = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_strings; i++) {
        char* cleaned = remove_whitespaces(test_strings[i]);
        if (cleaned != NULL) {
            printf("%s\n", cleaned);
            free(cleaned);
        } else {
            printf("Error processing string\n");
        }
    }

    return 0;
}