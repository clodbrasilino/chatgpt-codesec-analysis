#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t result_size = input_len + 1;
    char* result = (char*)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t src_idx = 0;
    size_t dst_idx = 0;

    while (src_idx < input_len) {
        if (isdigit((unsigned char)input[src_idx])) {
            size_t num_start = src_idx;
            while (src_idx < input_len && isdigit((unsigned char)input[src_idx])) {
                src_idx++;
            }
            size_t num_len = src_idx - num_start;

            char* num_str = (char*)malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }

            if (num_len > 0) {
                memcpy(num_str, input + num_start, num_len);
            }
            num_str[num_len] = '\0';

            errno = 0;
            long long num_val = strtoll(num_str, NULL, 10);
            free(num_str);

            if (errno == ERANGE) {
                free(result);
                return NULL;
            }

            long long new_val;
            if ((k > 0 && num_val > LLONG_MAX - k) || (k < 0 && num_val < LLONG_MIN - k)) {
                free(result);
                return NULL;
            }
            new_val = num_val + k;

            char new_num_str[64];
            int written = snprintf(new_num_str, sizeof(new_num_str), "%lld", new_val);
            if (written < 0 || (size_t)written >= sizeof(new_num_str)) {
                free(result);
                return NULL;
            }

            size_t new_num_len = (size_t)written;
            size_t remaining = input_len - src_idx;
            size_t needed_size = dst_idx + new_num_len + remaining + 1;

            if (needed_size > result_size) {
                char* temp = (char*)realloc(result, needed_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_size = needed_size;
            }

            memcpy(result + dst_idx, new_num_str, new_num_len);
            dst_idx += new_num_len;
        } else {
            if (dst_idx + 2 > result_size) {
                size_t new_size = result_size * 2;
                if (new_size < dst_idx + 2) {
                    new_size = dst_idx + 2;
                }
                char* temp = (char*)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_size = new_size;
            }
            result[dst_idx] = input[src_idx];
            dst_idx++;
            src_idx++;
        }
    }

    result[dst_idx] = '\0';

    char* final_result = (char*)realloc(result, dst_idx + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char* test1 = "abc123def456";
    char* result1 = increment_numeric_values(test1, 5);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    const char* test2 = "1a2b3c";
    char* result2 = increment_numeric_values(test2, 10);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    const char* test3 = "no numbers here";
    char* result3 = increment_numeric_values(test3, 100);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    const char* test4 = "123";
    char* result4 = increment_numeric_values(test4, 0);
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    char* result5 = increment_numeric_values(NULL, 5);
    if (result5 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}