#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int safe_strtoll(const char* str, size_t len, long long* out) {
    if (len == 0 || len >= 64) return 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[64];
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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

/* Possible weaknesses found:
 *  Shadowed declaration
 */
static size_t num_len(long long val) {
    if (val == 0) return 1;
    size_t count = 0;
    if (val < 0) {
        count = 1;
        val = -val;
    }
    while (val > 0) {
        count++;
        val /= 10;
    }
    return count;
}

static void ll_to_str(long long val, char* out) {
    if (val == 0) {
        out[0] = '0';
        return;
    }
    char* p = out;
    if (val < 0) {
        *p++ = '-';
        val = -val;
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char tmp[32];
    int idx = 0;
    while (val > 0) {
        tmp[idx++] = (char)('0' + (val % 10));
        val /= 10;
    }
    while (idx > 0) {
        *p++ = tmp[--idx];
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    
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
            /* Possible weaknesses found:
             *  Shadow variable
             *  Local variable 'num_len' shadows outer function [shadowFunction]
             */
            size_t num_len = src_idx - num_start;

            long long num_val;
            if (!safe_strtoll(input + num_start, num_len, &num_val)) {
                free(result);
                return NULL;
            }

            long long new_val;
            if (!ll_add_safe(num_val, k, &new_val)) {
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             *  new_num_len is initialized
             *  Value stored to 'new_num_len' during its initialization is never read [deadcode.DeadStores]
             */
            size_t new_num_len = num_len;
            long long estimate = new_val;
            if (estimate == 0) {
                /* Possible weaknesses found:
                 *  Redundant initialization for 'new_num_len'. The initialized value is overwritten before it is read. [redundantInitialization]
                 *  new_num_len is overwritten
                 */
                new_num_len = 1;
            } else {
                size_t nlen = 0;
                long long abs_est = estimate < 0 ? -estimate : estimate;
                while (abs_est > 0) {
                    nlen++;
                    abs_est /= 10;
                }
                if (estimate < 0) nlen++;
                new_num_len = nlen;
            }

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

            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char num_buf[32];
            ll_to_str(new_val, num_buf);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t actual_len = strlen(num_buf);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
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

    /* Possible weaknesses found:
     *  Assignment 'result5=increment_numeric_values(NULL,5)', assigned value is 0
     *  Calling function 'increment_numeric_values' returns 0
     *  Variable 'result5' can be declared as pointer to const [constVariablePointer]
     */
    char* result5 = increment_numeric_values(NULL, 5);
    /* Possible weaknesses found:
     *  Condition 'result5==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result5==NULL' is always true
     */
    if (result5 == NULL) {
        printf("NULL input handled\n");
    }

    return 0;
}