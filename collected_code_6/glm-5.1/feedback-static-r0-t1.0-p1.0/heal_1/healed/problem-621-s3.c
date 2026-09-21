#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char *increment_string_numbers(const char *input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    size_t alloc_size = len + 1;
    char *result = malloc(alloc_size);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

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

            int num_len = snprintf(NULL, 0, "%ld", num);

            size_t required_size = res_idx + num_len + (len - i) + 1;
            if (required_size > alloc_size) {
                char *temp = realloc(result, required_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                alloc_size = required_size;
            }

            snprintf(result + res_idx, num_len + 1, "%ld", num);
            res_idx += num_len;
        } else {
            if (res_idx + 1 >= alloc_size) {
                size_t required_size = alloc_size * 2;
                char *temp = realloc(result, required_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                alloc_size = required_size;
            }
            result[res_idx++] = input[i++];
        }
    }

    result[res_idx] = '\0';

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