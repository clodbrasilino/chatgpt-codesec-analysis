#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

char* increment_string_number(const char* str, int k) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    size_t temp_num_capacity = len + 1;
    char* temp_num = malloc(temp_num_capacity);
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
            if (num_len + 1 > temp_num_capacity) {
                free(temp_num);
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp_num, str + num_start, num_len);
            temp_num[num_len] = '\0';

            char* endptr;
            errno = 0;
            long val = strtol(temp_num, &endptr, 10);
            if (*endptr != '\0' || errno == ERANGE) {
                free(temp_num);
                free(result);
                return NULL;
            }
            
            if ((k > 0 && val > LONG_MAX - k) || (k < 0 && val < LONG_MIN - k)) {
                free(temp_num);
                free(result);
                return NULL;
            }
            val += k;

            int written = snprintf(result + res_idx, result_capacity - res_idx, "%ld", val);
            if (written < 0) {
                free(temp_num);
                free(result);
                return NULL;
            }
            
            if (res_idx + written + 1 >= result_capacity) {
                size_t new_capacity = res_idx + written + 32;
                char* new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(temp_num);
                    free(result);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
                snprintf(result + res_idx, result_capacity - res_idx, "%ld", val);
            }
            res_idx += written;
        } else {
            if (res_idx + 2 >= result_capacity) {
                size_t new_capacity = result_capacity + 32;
                char* new_result = realloc(result, new_capacity);
                if (new_result == NULL) {
                    free(temp_num);
                    free(result);
                    return NULL;
                }
                result = new_result;
                result_capacity = new_capacity;
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