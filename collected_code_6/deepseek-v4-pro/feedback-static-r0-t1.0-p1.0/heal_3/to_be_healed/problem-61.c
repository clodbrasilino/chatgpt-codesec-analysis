#include <stdio.h>
#include <string.h>

int count_substrings_with_sum_equal_length(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = (int)strlen(str);
    int count = 0;
    int prefix_sum[100001];

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

    size_t input_len = strcspn(input, "\n");
    input[input_len] = '\0';

    if (input[0] == '\0') {
        printf("0\n");
        return 0;
    }

    if (input_len >= sizeof(input) - 1) {
        printf("Invalid input\n");
        return 1;
    }

    for (size_t i = 0; i < input_len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid input\n");
            return 1;
        }
    }

    int result = count_substrings_with_sum_equal_length(input);
    printf("%d\n", result);

    return 0;
}