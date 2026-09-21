#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

static int safe_add(long long num, int k, long long *result) {
    if (k > 0) {
        if (num > LLONG_MAX - k) {
            return 0;
        }
    } else if (k < 0) {
        if (num < LLONG_MIN - k) {
            return 0;
        }
    }
    *result = num + k;
    return 1;
}

static char* extract_number(const char *input, size_t start, size_t len) {
    if (len == 0 || len >= SIZE_MAX) {
        return NULL;
    }
    char *num_str = (char*)malloc(len + 1);
    if (num_str == NULL) {
        return NULL;
    }
    memcpy(num_str, input + start, len);
    num_str[len] = '\0';
    return num_str;
}

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len >= SIZE_MAX / 20) {
        return NULL;
    }

    size_t max_result_size = input_len * 20 + 1;
    char *result = (char*)malloc(max_result_size);
    if (result == NULL) {
        return NULL;
    }

    size_t result_pos = 0;
    size_t i = 0;

    while (i < input_len) {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < input_len && isdigit((unsigned char)input[i])) {
                i++;
            }

            size_t num_len = i - start;
            char *num_str = extract_number(input, start, num_len);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }

            errno = 0;
            char *endptr = NULL;
            long long num = strtoll(num_str, &endptr, 10);
            free(num_str);

            if (errno == ERANGE || endptr == num_str || *endptr != '\0') {
                free(result);
                return NULL;
            }

            long long new_num;
            if (!safe_add(num, k, &new_num)) {
                free(result);
                return NULL;
            }

            char new_num_str[64];
            int written = snprintf(new_num_str, sizeof(new_num_str), "%lld", new_num);
            if (written < 0 || (size_t)written >= sizeof(new_num_str)) {
                free(result);
                return NULL;
            }

            size_t new_num_len = (size_t)written;
            if (result_pos + new_num_len >= max_result_size) {
                free(result);
                return NULL;
            }

            memcpy(result + result_pos, new_num_str, new_num_len);
            result_pos += new_num_len;
        } else {
            if (result_pos >= max_result_size) {
                free(result);
                return NULL;
            }
            result[result_pos++] = input[i++];
        }
    }

    if (result_pos >= max_result_size) {
        free(result);
        return NULL;
    }
    result[result_pos] = '\0';
    return result;
}

int main() {
    const char* test1 = "I have 10 apples and 5 oranges";
    const char* test2 = "Numbers: 1, 2, 3, 100";
    const char* test3 = "No numbers here";
    const char* test4 = "Edge case 999999999999999999";
    const char* test5 = "";

    char* result1 = increment_numeric_values(test1, 5);
    char* result2 = increment_numeric_values(test2, -2);
    char* result3 = increment_numeric_values(test3, 10);
    char* result4 = increment_numeric_values(test4, 1);
    char* result5 = increment_numeric_values(test5, 3);
    char* result6 = increment_numeric_values(NULL, 5);

    printf("Original: %s\n", test1);
    if (result1 != NULL) {
        printf("Result (+5): %s\n\n", result1);
        free(result1);
    } else {
        printf("Result (+5): Error\n\n");
    }

    printf("Original: %s\n", test2);
    if (result2 != NULL) {
        printf("Result (-2): %s\n\n", result2);
        free(result2);
    } else {
        printf("Result (-2): Error\n\n");
    }

    printf("Original: %s\n", test3);
    if (result3 != NULL) {
        printf("Result (+10): %s\n\n", result3);
        free(result3);
    } else {
        printf("Result (+10): Error\n\n");
    }

    printf("Original: %s\n", test4);
    if (result4 != NULL) {
        printf("Result (+1): %s\n\n", result4);
        free(result4);
    } else {
        printf("Result (+1): Error\n\n");
    }

    printf("Original: '%s'\n", test5);
    if (result5 != NULL) {
        printf("Result (+3): '%s'\n\n", result5);
        free(result5);
    } else {
        printf("Result (+3): Error\n\n");
    }

    printf("Original: NULL\n");
    if (result6 != NULL) {
        printf("Result: %s\n", result6);
        free(result6);
    } else {
        printf("Result: NULL\n");
    }

    return 0;
}