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

static char* safe_strtoll(const char* str, long long* out) {
    char* endptr;
    errno = 0;
    *out = strtoll(str, &endptr, 10);
    if (errno == ERANGE) return NULL;
    if (endptr == str) return NULL;
    if (*endptr != '\0') return NULL;
    return endptr;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t result_size = len + 32;
    char* result = malloc(result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t res_pos = 0;
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)input[i]) || 
            (input[i] == '-' && i + 1 < len && isdigit((unsigned char)input[i + 1]))) {
            
            int is_negative = 0;
            size_t start = i;
            
            if (input[i] == '-') {
                is_negative = 1;
                i++;
            }
            
            size_t num_start = i;
            while (i < len && isdigit((unsigned char)input[i])) {
                i++;
            }
            size_t num_end = i;
            size_t num_len = num_end - num_start;
            
            size_t leading_zeros = 0;
            for (size_t j = num_start; j < num_end; j++) {
                if (input[j] == '0') {
                    leading_zeros++;
                } else {
                    break;
                }
            }
            
            size_t total_len = num_len + (is_negative ? 1 : 0);
            
            char* num_str = malloc(total_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            
            if (is_negative) {
                num_str[0] = '-';
                memcpy(num_str + 1, input + num_start, num_len);
            } else {
                memcpy(num_str, input + num_start, num_len);
            }
            num_str[total_len] = '\0';
            
            long long num;
            if (safe_strtoll(num_str, &num) == NULL) {
                free(num_str);
                size_t copy_len = i - start;
                
                if (res_pos + copy_len + 1 >= result_size) {
                    while (result_size < res_pos + copy_len + 1) {
                        result_size *= 2;
                    }
                    char* tmp = realloc(result, result_size);
                    if (tmp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = tmp;
                }
                
                memcpy(result + res_pos, input + start, copy_len);
                res_pos += copy_len;
                continue;
            }
            free(num_str);
            
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
            
            int preserve_original_length = (leading_zeros > 0 && num == 0);
            
            if (new_num >= 0) {
                long long abs_val = new_num;
                int new_digits = count_digits(abs_val);
                if (abs_val == 0) new_digits = 1;
                
                size_t output_len;
                if (preserve_original_length) {
                    output_len = num_len;
                } else {
                    output_len = (size_t)new_digits > num_len ? (size_t)new_digits : num_len;
                }
                
                if (res_pos + output_len + 1 >= result_size) {
                    while (result_size < res_pos + output_len + 1) {
                        result_size *= 2;
                    }
                    char* tmp = realloc(result, result_size);
                    if (tmp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = tmp;
                }
                
                if (overflow || preserve_original_length) {
                    int zeros_to_pad = (int)output_len - new_digits;
                    if (zeros_to_pad < 0) zeros_to_pad = 0;
                    
                    for (int z = 0; z < zeros_to_pad; z++) {
                        result[res_pos + z] = '0';
                    }
                    
                    int printed = snprintf(result + res_pos + zeros_to_pad,
                                           result_size - res_pos - zeros_to_pad,
                                           "%lld", abs_val);
                    if (printed < 0) {
                        free(result);
                        return NULL;
                    }
                    res_pos += zeros_to_pad + printed;
                } else {
                    int printed = snprintf(result + res_pos,
                                           result_size - res_pos,
                                           "%lld", abs_val);
                    if (printed < 0) {
                        free(result);
                        return NULL;
                    }
                    res_pos += printed;
                }
            } else {
                long long abs_val = -new_num;
                int new_digits = count_digits(abs_val);
                
                size_t output_len;
                if (preserve_original_length) {
                    output_len = total_len;
                } else {
                    int required_digits = new_digits + 1;
                    output_len = required_digits > (int)total_len ? (size_t)required_digits : total_len;
                }
                
                if (res_pos + output_len + 1 >= result_size) {
                    while (result_size < res_pos + output_len + 1) {
                        result_size *= 2;
                    }
                    char* tmp = realloc(result, result_size);
                    if (tmp == NULL) {
                        free(result);
                        return NULL;
                    }
                    result = tmp;
                }
                
                result[res_pos] = '-';
                int zeros_to_pad = (int)output_len - 1 - new_digits;
                if (zeros_to_pad < 0) zeros_to_pad = 0;
                
                for (int z = 0; z < zeros_to_pad; z++) {
                    result[res_pos + 1 + z] = '0';
                }
                
                int printed = snprintf(result + res_pos + 1 + zeros_to_pad,
                                       result_size - res_pos - 1 - zeros_to_pad,
                                       "%lld", abs_val);
                if (printed < 0) {
                    free(result);
                    return NULL;
                }
                res_pos += 1 + zeros_to_pad + printed;
            }
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