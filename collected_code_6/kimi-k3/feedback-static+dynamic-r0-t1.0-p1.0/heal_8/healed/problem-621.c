#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define MAX_STRING_LEN 1024
#define MAX_NUM_LEN 32

int increment_numeric_values(char *str, size_t str_size, long k) {
    if (str == NULL || k < 0 || str_size == 0 || str_size > MAX_STRING_LEN) {
        return -1;
    }

    size_t len = strnlen(str, str_size);
    if (len == 0 || len >= MAX_STRING_LEN || len >= str_size) {
        return -1;
    }

    char *result = malloc(MAX_STRING_LEN);
    if (result == NULL) {
        return -1;
    }

    size_t i = 0;
    size_t res_idx = 0;
    int found_number = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            found_number = 1;
            size_t num_start = i;
            
            while (i < len && isdigit((unsigned char)str[i])) {
                i++;
            }
            
            size_t num_len = i - num_start;
            char num_buf[MAX_NUM_LEN];
            
            if (num_len >= sizeof(num_buf)) {
                free(result);
                return -1;
            }
            
            if (num_len > 0 && num_len < sizeof(num_buf)) {
                memcpy(num_buf, str + num_start, num_len);
                num_buf[num_len] = '\0';
            } else {
                free(result);
                return -1;
            }
            
            char *endptr;
            errno = 0;
            long num = strtol(num_buf, &endptr, 10);
            
            if (errno != 0 || *endptr != '\0' || endptr == num_buf) {
                free(result);
                return -1;
            }
            
            if (num > LONG_MAX - k) {
                free(result);
                return -1;
            }
            
            long new_value = num + k;
            if (new_value < 0 || new_value > 999999999) {
                free(result);
                return -1;
            }
            
            if (res_idx >= MAX_STRING_LEN - 1) {
                free(result);
                return -1;
            }
            
            int written = snprintf(result + res_idx, MAX_STRING_LEN - res_idx, "%ld", new_value);
            if (written < 0 || (size_t)written >= MAX_STRING_LEN - res_idx) {
                free(result);
                return -1;
            }
            
            res_idx += (size_t)written;
        } else {
            if (res_idx >= MAX_STRING_LEN - 1) {
                free(result);
                return -1;
            }
            result[res_idx++] = str[i++];
        }
    }
    
    if (res_idx >= MAX_STRING_LEN) {
        free(result);
        return -1;
    }
    
    result[res_idx] = '\0';
    
    if (!found_number) {
        free(result);
        return -1;
    }
    
    if (res_idx >= MAX_STRING_LEN || res_idx >= str_size) {
        free(result);
        return -1;
    }
    
    size_t result_len = strnlen(result, MAX_STRING_LEN);
    if (result_len < str_size && result_len < MAX_STRING_LEN) {
        if (result_len + 1 <= str_size && result_len + 1 <= MAX_STRING_LEN) {
            memcpy(str, result, result_len + 1);
        } else {
            free(result);
            return -1;
        }
    } else {
        free(result);
        return -1;
    }
    
    free(result);
    return 0;
}

int main(void) {
    char test1[MAX_STRING_LEN] = "abc123def456";
    char test2[MAX_STRING_LEN] = "value: 42, count: 100";
    char test3[MAX_STRING_LEN] = "no numbers here";
    char test4[MAX_STRING_LEN] = "999999999";
    
    long k = 5;
    
    printf("Original: %s\n", test1);
    if (increment_numeric_values(test1, sizeof(test1), k) == 0) {
        printf("Modified: %s\n", test1);
    } else {
        printf("Error processing string\n");
    }
    
    printf("\nOriginal: %s\n", test2);
    if (increment_numeric_values(test2, sizeof(test2), k) == 0) {
        printf("Modified: %s\n", test2);
    } else {
        printf("Error processing string\n");
    }
    
    printf("\nOriginal: %s\n", test3);
    if (increment_numeric_values(test3, sizeof(test3), k) == 0) {
        printf("Modified: %s\n", test3);
    } else {
        printf("Error processing string\n");
    }
    
    printf("\nOriginal: %s\n", test4);
    if (increment_numeric_values(test4, sizeof(test4), k) == 0) {
        printf("Modified: %s\n", test4);
    } else {
        printf("Error processing string\n");
    }
    
    return 0;
}