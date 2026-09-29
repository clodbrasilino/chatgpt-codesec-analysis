#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    if (*input == '\0') {
        char *result = (char *)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
        if (input_len > 1024 * 1024) {
            return NULL;
        }
    }

    size_t max_output_len = input_len * 2 + 1;
    char *result = (char *)malloc(max_output_len);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;

    for (size_t i = 0; i < input_len; i++) {
        char c = input[i];

        if (i > 0 && isupper((unsigned char)c)) {
            int prev_is_lower = islower((unsigned char)input[i - 1]);
            int next_is_lower = (i + 1 < input_len) && islower((unsigned char)input[i + 1]);

            if (prev_is_lower || next_is_lower) {
                if (dst_pos + 1 >= max_output_len) {
                    size_t new_size = max_output_len * 2;
                    char *new_result = (char *)realloc(result, new_size);
                    if (new_result == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    max_output_len = new_size;
                }
                result[dst_pos++] = '_';
            }
        }

        if (dst_pos + 1 >= max_output_len) {
            size_t new_size = max_output_len * 2;
            char *new_result = (char *)realloc(result, new_size);
            if (new_result == NULL) {
                free(result);
                return NULL;
            }
            result = new_result;
            max_output_len = new_size;
        }
        result[dst_pos++] = (char)tolower((unsigned char)c);
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
        "convertJSONToXML",
        "googleAssistant",
        "chromeCast",
        "quadCore"
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