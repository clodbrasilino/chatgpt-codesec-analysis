#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char *increment_string_numbers(const char *input, int k) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;
    size_t capacity = len + 1;

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            long num = 0;
            while (i < len && isdigit((unsigned char)input[i])) {
                int digit = input[i] - '0';
                if (num > (LONG_MAX - digit) / 10) {
                    num = LONG_MAX;
                } else {
                    num = num * 10 + digit;
                }
                i++;
            }

            num += k;

            if (num < 0) {
                num = 0;
            }

            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char num_buf[32];
            int num_len = snprintf(num_buf, sizeof(num_buf), "%ld", num);
            if (num_len < 0) {
                free(result);
                return NULL;
            }
            if ((size_t)num_len >= sizeof(num_buf)) {
                num_len = sizeof(num_buf) - 1;
            }

            size_t remaining_len = len - i;
            if (num_len > SIZE_MAX - remaining_len - 1 || res_idx > SIZE_MAX - num_len - remaining_len - 1) {
                free(result);
                return NULL;
            }
            size_t new_size = res_idx + num_len + remaining_len + 1;

            if (new_size > capacity) {
                char *temp = realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                capacity = new_size;
            }

            if (res_idx + num_len <= capacity) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, num_buf, num_len);
            }
            res_idx += num_len;
        } else {
            size_t required_size = res_idx + (len - i) + 1;
            if (required_size > capacity) {
                char *temp = realloc(result, required_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                capacity = required_size;
            }
            if (res_idx < capacity) {
                result[res_idx++] = input[i++];
            }
        }
    }

    if (res_idx < SIZE_MAX) {
        result[res_idx] = '\0';
    }

    char *final_result = realloc(result, res_idx + 1);
    if (final_result != NULL) {
        result = final_result;
    }

    return result;
}

int main(void) {
    const char *str = "abc123def45gh6";
    int k = 7;

    char *incremented = increment_string_numbers(str, k);
    if (incremented != NULL) {
        printf("Original: %s\n", str);
        printf("Incremented: %s\n", incremented);
        free(incremented);
    }

    return 0;
}