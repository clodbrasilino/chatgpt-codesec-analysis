#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char** split_at_uppercase(const char* input, int* count) {
    if (input == NULL || count == NULL) {
        if (count != NULL) *count = 0;
        return NULL;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        if (input_len == SIZE_MAX) {
            *count = 0;
            return NULL;
        }
        input_len++;
    }

    size_t capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) {
        *count = 0;
        return NULL;
    }

    *count = 0;
    size_t start = 0;

    for (size_t i = 0; i <= input_len; i++) {
        int is_uppercase = (i < input_len && isupper((unsigned char)input[i]));
        
        if (is_uppercase && i > start) {
            size_t len = i - start;
            
            if ((size_t)(*count) >= capacity) {
                size_t new_capacity = capacity * 2;
                if (new_capacity <= capacity) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }
                char** temp = realloc(result, new_capacity * sizeof(char*));
                if (!temp) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *count = 0;
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }

            if (len >= SIZE_MAX) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            char* segment = malloc(len + 1);
            if (!segment) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(segment, input + start, len);
            segment[len] = '\0';
            result[*count] = segment;
            (*count)++;
            start = i;
        }
    }

    if (start < input_len) {
        size_t len = input_len - start;
        
        if ((size_t)(*count) >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity <= capacity) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            char** temp = realloc(result, new_capacity * sizeof(char*));
            if (!temp) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }
            result = temp;
        }

        if (len >= SIZE_MAX) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            *count = 0;
            return NULL;
        }

        char* segment = malloc(len + 1);
        if (!segment) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            *count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(segment, input + start, len);
        segment[len] = '\0';
        result[*count] = segment;
        (*count)++;
    }

    return result;
}

int main(void) {
    const char* test_string = "HelloWorldThisIsATest";
    int count = 0;
    char** parts = split_at_uppercase(test_string, &count);

    if (parts) {
        printf("Split parts (%d):\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("Failed to split string\n");
    }

    return 0;
}