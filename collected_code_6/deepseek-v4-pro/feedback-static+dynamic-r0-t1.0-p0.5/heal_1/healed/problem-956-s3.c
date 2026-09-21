#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* input, int* count) {
    if (input == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }

    int input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
        if (input_len > 1000000) {
            *count = 0;
            return NULL;
        }
    }

    int capacity = 10;
    char** result = malloc(capacity * sizeof(char*));
    if (!result) {
        *count = 0;
        return NULL;
    }

    *count = 0;
    int start = 0;

    for (int i = 0; i <= input_len; i++) {
        int is_uppercase = (i < input_len && isupper((unsigned char)input[i]));
        
        if (is_uppercase && i > start) {
            if (*count >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
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

            int len = i - start;
            result[*count] = malloc((len + 1) * sizeof(char));
            if (!result[*count]) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                *count = 0;
                return NULL;
            }

            memcpy(result[*count], input + start, len);
            result[*count][len] = '\0';
            (*count)++;
            start = i;
        }
    }

    if (start < input_len) {
        if (*count >= capacity) {
            capacity *= 2;
            char** temp = realloc(result, capacity * sizeof(char*));
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

        int len = input_len - start;
        result[*count] = malloc((len + 1) * sizeof(char));
        if (!result[*count]) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            *count = 0;
            return NULL;
        }

        memcpy(result[*count], input + start, len);
        result[*count][len] = '\0';
        (*count)++;
    }

    return result;
}

int main() {
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