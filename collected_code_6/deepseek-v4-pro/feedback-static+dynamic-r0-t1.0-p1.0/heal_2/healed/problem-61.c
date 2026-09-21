#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_substrings_with_sum_equal_length(const char *str, size_t len) {
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
    char input[100002];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }

    if (input_len == 0) {
        printf("0\n");
        return 0;
    }

    for (size_t i = 0; i < input_len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid input\n");
            return 1;
        }
    }

    int result = count_substrings_with_sum_equal_length(input, input_len);
    if (result < 0) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("%d\n", result);

    return 0;
}