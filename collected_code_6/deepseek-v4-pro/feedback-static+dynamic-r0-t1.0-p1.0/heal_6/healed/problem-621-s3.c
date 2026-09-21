#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int safe_strtoll(const char* str, size_t len, long long* out) {
    if (len == 0 || len >= 64) return 0;
    char buf[64];
    if (len >= sizeof(buf)) return 0;
    memcpy(buf, str, len);
    buf[len] = '\0';
    
    char* endptr = NULL;
    errno = 0;
    long long val = strtoll(buf, &endptr, 10);
    if (errno == ERANGE || endptr != buf + len) return 0;
    *out = val;
    return 1;
}

static int ll_add_safe(long long a, int b, long long* out) {
    if (b > 0) {
        if (a > LLONG_MAX - b) return 0;
    } else if (b < 0) {
        if (a < LLONG_MIN - b) return 0;
    }
    *out = a + b;
    return 1;
}

static size_t get_num_len(long long val) {
    if (val == 0) return 1;
    size_t count = 0;
    long long temp_val = val;
    if (temp_val < 0) {
        count = 1;
        temp_val = -temp_val;
    }
    while (temp_val > 0) {
        count++;
        temp_val /= 10;
    }
    return count;
}

static void ll_to_str(long long val, char* out) {
    if (val == 0) {
        out[0] = '0';
        out[1] = '\0';
        return;
    }
    char* p = out;
    long long temp_val = val;
    if (temp_val < 0) {
        *p++ = '-';
        temp_val = -temp_val;
    }
    char tmp[32];
    int idx = 0;
    while (temp_val > 0) {
        tmp[idx++] = (char)('0' + (temp_val % 10));
        temp_val /= 10;
    }
    while (idx > 0) {
        *p++ = tmp[--idx];
    }
    *p = '\0';
}

static size_t calc_new_num_len(long long val) {
    if (val == 0) return 1;
    size_t nlen = 0;
    long long abs_val = val < 0 ? -val : val;
    while (abs_val > 0) {
        nlen++;
        abs_val /= 10;
    }
    if (val < 0) nlen++;
    return nlen;
}

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len == 0) {
        char* empty_result = (char*)malloc(1);
        if (empty_result == NULL) return NULL;
        empty_result[0] = '\0';
        return empty_result;
    }
    
    size_t result_capacity = input_len + 1;
    char* result = (char*)malloc(result_capacity);
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
            size_t parsed_num_len = src_idx - num_start;

            long long num_val;
            if (!safe_strtoll(input + num_start, parsed_num_len, &num_val)) {
                free(result);
                return NULL;
            }

            long long new_val;
            if (!ll_add_safe(num_val, k, &new_val)) {
                free(result);
                return NULL;
            }

            size_t new_num_len = calc_new_num_len(new_val);

            size_t remaining = input_len - src_idx;
            size_t needed = dst_idx + new_num_len + remaining + 1;

            if (needed > result_capacity) {
                size_t new_cap = result_capacity * 2;
                if (new_cap < needed) new_cap = needed;
                char* temp = (char*)realloc(result, new_cap);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_capacity = new_cap;
            }

            char num_buf[32];
            ll_to_str(new_val, num_buf);
            size_t actual_len = strlen(num_buf);
            memcpy(result + dst_idx, num_buf, actual_len);
            dst_idx += actual_len;
        } else {
            if (dst_idx + 2 > result_capacity) {
                size_t new_cap = result_capacity * 2;
                if (new_cap < dst_idx + 2) new_cap = dst_idx + 2;
                char* temp = (char*)realloc(result, new_cap);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_capacity = new_cap;
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

    const char* test6 = "999999999999999999";
    char* result6 = increment_numeric_values(test6, 1);
    if (result6 != NULL) {
        printf("%s\n", result6);
        free(result6);
    }

    const char* test7 = "";
    char* result7 = increment_numeric_values(test7, 10);
    if (result7 != NULL) {
        printf("'%s'\n", result7);
        free(result7);
    }

    return 0;
}