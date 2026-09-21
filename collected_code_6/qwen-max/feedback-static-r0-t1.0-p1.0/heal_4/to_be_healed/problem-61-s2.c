#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubstringsWithSum(const int *digits, int len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        int sum = 0;
        for (int j = i; j < len; j++) {
            sum += digits[j];
            if (sum == (j - i + 1)) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return 1;
    }
    input[strcspn(input, "\n")] = 0;

    int len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (input[len] != '\0' && len < 1023 && input[len] >= '0' && input[len] <= '9') {
        len++;
    }

    if (len == 1023 || input[len] != '\0') {
        fprintf(stderr, "Input too long or contains non-digit characters\n");
        return 1;
    }

    int *digits = (int *)malloc(len * sizeof(int));
    if (digits == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < len; i++) {
        digits[i] = input[i] - '0';
    }

    int result = countSubstringsWithSum(digits, len);
    printf("%d\n", result);

    free(digits);
    return 0;
}