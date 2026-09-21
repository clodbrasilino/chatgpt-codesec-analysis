#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_substrings(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    int count = 0;
    int *prefix = (int *)malloc((n + 1) * sizeof(int));
    if (prefix == NULL) {
        return -1;
    }
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] < '0' || str[i] > '9') {
            free(prefix);
            return -1;
        }
        prefix[i + 1] = prefix[i] + (str[i] - '0');
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int sum = prefix[i + len] - prefix[i];
            if (sum == len) {
                count++;
            }
        }
    }
    free(prefix);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    printf("Enter a numeric string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    if (len == 0) {
        printf("0\n");
        return 0;
    }
    int result = count_substrings(input);
    if (result < 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("%d\n", result);
    return 0;
}