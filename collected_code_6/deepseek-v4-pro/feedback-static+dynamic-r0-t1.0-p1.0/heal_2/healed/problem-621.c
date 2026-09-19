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
    size_t result_size = len * 2 + 32;
    char* result = malloc(result_size);
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

            int leading_zeros = 0;
            for (size_t j = start; j < i; j++) {
                if (input[j] == '0') {
                    leading_zeros++;
                } else {
                    break;
                }
            }

            char* num_str = malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            memcpy(num_str, input + start, num_len);
            num_str[num_len] = '\0';

            char* endptr;
            errno = 0;
            long long num = strtoll(num_str, &endptr, 10);
            if (errno == ERANGE || endptr == num_str) {
                free(num_str);
                free(result);
                return NULL;
            }

            long long new_num;
            if (k > 0 && num > LLONG_MAX - k) {
                new_num = LLONG_MAX;
            } else if (k < 0 && num < LLONG_MIN - k) {
                new_num = LLONG_MIN;
            } else {
                new_num = num + k;
            }

            while (res_pos + num_len + 32 >= result_size) {
                result_size *= 2;
                char* tmp = realloc(result, result_size);
                if (tmp == NULL) {
                    free(num_str);
                    free(result);
                    return NULL;
                }
                result = tmp;
            }

            int written;
            if (new_num < 0) {
                written = snprintf(result + res_pos, result_size - res_pos, "%lld", new_num);
            } else if (new_num == 0 && num_len > 1 && leading_zeros == (int)num_len) {
                written = 0;
                for (int z = 0; z < (int)num_len - 1; z++) {
                    result[res_pos + written] = '0';
                    written++;
                }
                result[res_pos + written] = '0';
                written++;
            } else if (leading_zeros > 0 && new_num > 0) {
                written = 0;
                long long temp = new_num;
                int digits = 0;
                if (temp == 0) digits = 1;
                else {
                    while (temp > 0) {
                        temp /= 10;
                        digits++;
                    }
                }
                int total_digits = leading_zeros + digits;
                if (total_digits > (int)num_len) total_digits = (int)num_len;
                int zeros_to_print = total_digits - digits;
                for (int z = 0; z < zeros_to_print; z++) {
                    result[res_pos + written] = '0';
                    written++;
                }
                int printed = snprintf(result + res_pos + written, result_size - res_pos - written, "%lld", new_num);
                if (printed < 0 || (size_t)printed >= result_size - res_pos - written) {
                    free(num_str);
                    free(result);
                    return NULL;
                }
                written += printed;
            } else {
                written = snprintf(result + res_pos, result_size - res_pos, "%lld", new_num);
            }

            if (written < 0 || (size_t)written >= result_size - res_pos) {
                free(num_str);
                free(result);
                return NULL;
            }
            res_pos += written;
            free(num_str);
        } else {
            if (res_pos + 1 >= result_size) {
                result_size *= 2;
                char* tmp = realloc(result, result_size);
                if (tmp == NULL) {
                    free(result);
                    return NULL;
                }
                result = tmp;
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

    char* endptr;
    errno = 0;
    long k_val = strtol(argv[2], &endptr, 10);
    if (endptr == argv[2] || *endptr != '\0' || errno == ERANGE) {
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