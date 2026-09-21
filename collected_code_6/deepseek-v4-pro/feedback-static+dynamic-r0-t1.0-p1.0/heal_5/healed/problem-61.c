#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int count_substrings_with_sum_equal_length(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return 0;
    }

    if (len > 100000) {
        return -1;
    }

    int count = 0;
    
    int *prefix_sum = (int *)malloc((len + 2) * sizeof(int));
    if (prefix_sum == NULL) {
        return -1;
    }

    prefix_sum[0] = 0;
    for (size_t i = 0; i < len; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + (str[i] - '0');
    }

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j <= len; j++) {
            size_t substring_len = j - i;
            int sum = prefix_sum[j] - prefix_sum[i];
            if (sum == (int)substring_len) {
                count++;
            }
        }
    }

    free(prefix_sum);
    return count;
}

int main(void) {
    char *input_buffer = (char *)malloc(100002 * sizeof(char));
    if (input_buffer == NULL) {
        return 1;
    }

    if (fgets(input_buffer, 100002, stdin) == NULL) {
        free(input_buffer);
        return 1;
    }

    size_t input_len = strnlen(input_buffer, 100002);
    if (input_len > 0 && input_buffer[input_len - 1] == '\n') {
        input_buffer[input_len - 1] = '\0';
        input_len--;
    }

    if (input_len == 0) {
        printf("0\n");
        free(input_buffer);
        return 0;
    }

    if (input_len >= 100001) {
        printf("Input too long\n");
        free(input_buffer);
        return 1;
    }

    for (size_t i = 0; i < input_len; i++) {
        if (input_buffer[i] < '0' || input_buffer[i] > '9') {
            printf("Invalid input\n");
            free(input_buffer);
            return 1;
        }
    }

    int result = count_substrings_with_sum_equal_length(input_buffer, input_len);
    if (result < 0) {
        printf("Memory allocation failed\n");
        free(input_buffer);
        return 1;
    }

    printf("%d\n", result);

    free(input_buffer);
    return 0;
}