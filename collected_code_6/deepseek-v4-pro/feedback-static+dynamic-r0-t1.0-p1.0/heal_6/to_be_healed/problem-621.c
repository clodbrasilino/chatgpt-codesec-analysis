#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

static int count_digits(long long num) {
    int count = 0;
    if (num == 0) return 1;
    while (num != 0) {
        num /= 10;
        count++;
    }
    return count;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  */

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
            if (errno == ERANGE || endptr == num_str || *endptr != '\0') {
                free(num_str);
                free(result);
                return NULL;
            }

            long long new_num;
            int overflow = 0;
            if (k > 0 && num > LLONG_MAX - k) {
                new_num = LLONG_MAX;
                overflow = 1;
            } else if (k < 0 && num < LLONG_MIN - k) {
                new_num = LLONG_MIN;
                overflow = 1;
            } else {
                new_num = num + k;
            }

            while (res_pos + num_len + 64 >= result_size) {
                result_size *= 2;
                char* tmp = realloc(result, result_size);
                if (tmp == NULL) {
                    free(num_str);
                    free(result);
                    return NULL;
                }
                result = tmp;
            }

            int written = 0;

            if (overflow) {
                char fmt_buf[64];
                int fmt_len = snprintf(fmt_buf, sizeof(fmt_buf), "%lld", new_num);
                if (fmt_len < 0) {
                    free(num_str);
                    free(result);
                    return NULL;
                }
                memcpy(result + res_pos, fmt_buf, fmt_len);
                written = fmt_len;
            } else if (new_num == 0) {
                if (leading_zeros == (int)num_len) {
                    for (size_t z = 0; z < num_len; z++) {
                        result[res_pos + z] = '0';
                    }
                    written = (int)num_len;
                } else {
                    result[res_pos] = '0';
                    written = 1;
                }
            } else if (new_num > 0) {
                int digits = count_digits(new_num);
                int total_digits = leading_zeros + digits;
                if (total_digits < (int)num_len) {
                    total_digits = (int)num_len;
                }
                int zeros_to_write = total_digits - digits;
                for (int z = 0; z < zeros_to_write; z++) {
                    result[res_pos + z] = '0';
                }
                int printed = snprintf(result + res_pos + zeros_to_write, 
                                       result_size - res_pos - zeros_to_write, 
                                       "%lld", new_num);
                if (printed < 0) {
                    free(num_str);
                    free(result);
                    return NULL;
                }
                written = zeros_to_write + printed;
            } else {
                result[res_pos] = '-';
                long long abs_val = -new_num;
                int digits = count_digits(abs_val);
                int total_digits = leading_zeros + digits;
                if (total_digits < (int)num_len - 1) {
                    total_digits = (int)num_len - 1;
                }
                int zeros_to_write = total_digits - digits;
                for (int z = 0; z < zeros_to_write; z++) {
                    result[res_pos + 1 + z] = '0';
                }
                int printed = snprintf(result + res_pos + 1 + zeros_to_write,
                                       result_size - res_pos - 1 - zeros_to_write,
                                       "%lld", abs_val);
                if (printed < 0) {
                    free(num_str);
                    free(result);
                    return NULL;
                }
                written = 1 + zeros_to_write + printed;
            }

            res_pos += written;
            free(num_str);
        } else {
            if (res_pos + 2 >= result_size) {
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