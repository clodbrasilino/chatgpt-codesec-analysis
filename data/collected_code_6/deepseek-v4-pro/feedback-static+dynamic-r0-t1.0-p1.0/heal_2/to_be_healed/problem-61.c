#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_substrings_with_sum_equal_length(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int count = 0;
    
    int *prefix_sum = (int *)malloc((len + 2) * sizeof(int));
    if (prefix_sum == NULL) {
        return -1;
    }

    prefix_sum[0] = 0;
    for (int i = 0; i < len; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + (str[i] - '0');
    }

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j <= len; j++) {
            int substring_len = j - i;
            int sum = prefix_sum[j] - prefix_sum[i];
            if (sum == substring_len) {
                count++;
            }
        }
    }

    free(prefix_sum);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[100002];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t newline_pos = strcspn(input, "\n");
    if (newline_pos < sizeof(input)) {
        input[newline_pos] = '\0';
    }

    if (input[0] == '\0') {
        printf("0\n");
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    for (size_t i = 0; i < input_len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid input\n");
            return 1;
        }
    }

    int result = count_substrings_with_sum_equal_length(input);
    if (result < 0) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("%d\n", result);

    return 0;
}