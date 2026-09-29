#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t result_capacity = len * 2 + 1;
    char* result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t res_pos = 0;
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < len && isdigit((unsigned char)input[i])) {
                i++;
            }
            size_t num_len = i - start;
            char* num_str = malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            if (num_len > 0) {
                memcpy(num_str, input + start, num_len);
            }
            num_str[num_len] = '\0';

            char* endptr;
            errno = 0;
            long long num = strtoll(num_str, &endptr, 10);
            if (errno == ERANGE || endptr == num_str || *endptr != '\0') {
                free(num_str);
                free(result);
                return NULL;
            }

            long long new_num;
            if (k > 0 && num > LLONG_MAX - k) {
                free(num_str);
                free(result);
                return NULL;
            }
            if (k < 0 && num < LLONG_MIN - k) {
                free(num_str);
                free(result);
                return NULL;
            }
            new_num = num + k;

            int written = snprintf(result + res_pos, result_capacity - res_pos, "%lld", new_num);
            if (written < 0 || (size_t)written >= result_capacity - res_pos) {
                free(num_str);
                free(result);
                return NULL;
            }
            res_pos += written;
            free(num_str);
        } else {
            if (res_pos >= result_capacity - 1) {
                free(result);
                return NULL;
            }
            result[res_pos++] = input[i];
            i++;
        }
    }

    result[res_pos] = '\0';
    return result;
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    size_t input_len = strlen(argv[1]);
    if (strlen(argv[2]) == 0) {
        fprintf(stderr, "Invalid integer for k\n");
        return 1;
    }

    char* endptr;
    errno = 0;
    long k_val = strtol(argv[2], &endptr, 10);
    if (errno == ERANGE || endptr == argv[2] || *endptr != '\0') {
        fprintf(stderr, "Invalid integer for k\n");
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