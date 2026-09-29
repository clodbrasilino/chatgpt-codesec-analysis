#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t max_result_size = input_len * 2 + 1;
    if (max_result_size <= input_len) {
        return NULL;
    }

    char *result = malloc(max_result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;
    size_t src_pos = 0;

    while (src_pos < input_len && dst_pos + 1 < max_result_size) {
        if (src_pos + 1 < input_len &&
            islower((unsigned char)input[src_pos]) &&
            isupper((unsigned char)input[src_pos + 1])) {
            
            result[dst_pos++] = (char)tolower((unsigned char)input[src_pos]);
            
            if (dst_pos + 1 < max_result_size) {
                result[dst_pos++] = '_';
            } else {
                break;
            }
            
            result[dst_pos++] = (char)tolower((unsigned char)input[src_pos + 1]);
            src_pos += 2;
        } else {
            result[dst_pos++] = (char)tolower((unsigned char)input[src_pos]);
            src_pos++;
        }
    }

    result[dst_pos] = '\0';

    size_t actual_len = strnlen(result, max_result_size);
    char *final_result = malloc(actual_len + 1);
    if (final_result != NULL) {
        if (actual_len + 1 > actual_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(final_result, result, actual_len + 1);
        }
    } else {
        free(result);
        return NULL;
    }

    free(result);
    return final_result;
}

int main(void) {
    const char *test_cases[] = {
        "googleAssistant",
        "chromeCast",
        "quadCore",
        "camelCase",
        "thisIsATest",
        "already_snake",
        "UPPERCASE",
        "mixedCASEString123",
        "a",
        "",
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