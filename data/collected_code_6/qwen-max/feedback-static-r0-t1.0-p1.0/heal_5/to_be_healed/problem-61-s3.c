#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str, size_t len) {
    int count = 0;
    for (size_t i = 0; i < len; i++) {
        int sum = 0, j = 0;
        while (i + j < len && (sum + (str[i + j] - '0')) <= (j + 1)) {
            sum += str[i + j] - '0';
            if (sum == j + 1) {
                count++;
            }
            j++;
        }
    }
    return count;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strnlen(input, sizeof(input));
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        int result = countSubstrings(input, len);
        printf("Count of substrings: %d\n", result);
    }
    return 0;
}