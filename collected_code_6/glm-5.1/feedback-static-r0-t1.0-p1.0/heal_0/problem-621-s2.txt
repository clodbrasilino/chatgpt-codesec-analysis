#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_string_number(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char* temp_num = malloc(len + 1);
    if (temp_num == NULL) {
        return NULL;
    }

    size_t result_capacity = len + 32;
    char* result = malloc(result_capacity);
    if (result == NULL) {
        free(temp_num);
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t num_start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }

            size_t num_len = i - num_start;
            if (num_len >= len + 1) {
                free(temp_num);
                free(result);
                return NULL;
            }

            memcpy(temp_num, str + num_start, num_len);
            temp_num[num_len] = '\0';

            long val = strtol(temp_num, NULL, 10);
            val += k;

            size_t required = res_idx + 32;
            if (required >= result_capacity) {
                result_capacity = required + 1;
                char* new_result = realloc(result, result_capacity);
                if (new_result == NULL) {
                    free(temp_num);
                    free(result);
                    return NULL;
                }
                result = new_result;
            }

            int written = snprintf(result + res_idx, result_capacity - res_idx, "%ld", val);
            if (written < 0) {
                free(temp_num);
                free(result);
                return NULL;
            }
            res_idx += written;
        } else {
            if (res_idx + 1 >= result_capacity) {
                result_capacity = res_idx + 32;
                char* new_result = realloc(result, result_capacity);
                if (new_result == NULL) {
                    free(temp_num);
                    free(result);
                    return NULL;
                }
                result = new_result;
            }
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
    free(temp_num);
    return result;
}

int main(void) {
    const char* inputs[] = {
        "abc123def456",
        "no_numbers_here",
        "100200300",
        "test0test",
        "-10+5",
        NULL
    };
    int k = 5;

    for (int i = 0; inputs[i] != NULL; i++) {
        char* incremented = increment_string_number(inputs[i], k);
        if (incremented != NULL) {
            printf("Original: %s, Incremented: %s\n", inputs[i], incremented);
            free(incremented);
        } else {
            printf("Failed to increment string: %s\n", inputs[i]);
        }
    }

    return 0;
}