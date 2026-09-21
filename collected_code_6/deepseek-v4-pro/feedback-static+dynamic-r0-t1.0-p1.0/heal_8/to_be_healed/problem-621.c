#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 1000000
#define MAX_NUMBER_LENGTH 32
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (len > MAX_INPUT_LENGTH) {
        return NULL;
    }

    size_t result_size = len * 2 + 1;
    if (result_size <= len || result_size > SIZE_MAX - 1) {
        return NULL;
    }

    char* result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t res_pos = 0;
    size_t i = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char num_str[MAX_NUMBER_LENGTH + 1];

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)input[i])) {
                i++;
            }
            size_t num_len = i - start;

            if (num_len > MAX_NUMBER_LENGTH || num_len == 0) {
                free(result);
                return NULL;
            }

            if (num_len >= sizeof(num_str)) {
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, input + start, num_len);
            num_str[num_len] = '\0';

            errno = 0;
            long long num = strtoll(num_str, NULL, 10);
            if (errno == ERANGE) {
                free(result);
                return NULL;
            }

            long long new_num;
            if (k > 0 && num > LLONG_MAX - k) {
                free(result);
                return NULL;
            }
            if (k < 0 && num < LLONG_MIN - k) {
                free(result);
                return NULL;
            }
            new_num = num + k;

            int required = snprintf(NULL, 0, "%lld", new_num);
            if (required < 0) {
                free(result);
                return NULL;
            }

            while ((size_t)required >= result_size - res_pos) {
                size_t new_result_size = result_size * 2;
                if (new_result_size <= result_size || new_result_size > SIZE_MAX - 1) {
                    free(result);
                    return NULL;
                }
                char* new_result = realloc(result, new_result_size);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                result_size = new_result_size;
            }

            int written = snprintf(result + res_pos, result_size - res_pos, "%lld", new_num);
            if (written < 0 || (size_t)written >= result_size - res_pos) {
                free(result);
                return NULL;
            }
            res_pos += written;
        } else {
            while (res_pos >= result_size - 1) {
                size_t new_result_size = result_size * 2;
                if (new_result_size <= result_size || new_result_size > SIZE_MAX - 1) {
                    free(result);
                    return NULL;
                }
                char* new_result = realloc(result, new_result_size);
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                result_size = new_result_size;
            }
            result[res_pos++] = input[i];
            i++;
        }
    }

    if (res_pos >= result_size) {
        free(result);
        return NULL;
    }
    result[res_pos] = '\0';
    return result;
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    size_t input_len = strnlen(argv[1], MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input string too long\n");
        return 1;
    }

    char* endptr;
    errno = 0;
    long k_val = strtol(argv[2], &endptr, 10);
    if (endptr == argv[2] || *endptr != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid integer for k\n");
        return 1;
    }

    if (k_val > INT_MAX || k_val < INT_MIN) {
        fprintf(stderr, "Integer k out of range\n");
        return 1;
    }

    char* result = increment_numeric_values(argv[1], (int)k_val);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);
    return 0;
}