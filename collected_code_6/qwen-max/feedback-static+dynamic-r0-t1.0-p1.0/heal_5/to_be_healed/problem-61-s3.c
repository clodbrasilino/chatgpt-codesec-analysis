#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    size_t len = strnlen(str, 1024);
    int count = 0;
    for (size_t i = 0; i < len; i++) {
        int sum = 0;
        size_t j = 0;
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
        input[strcspn(input, "\n")] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strlen(input) < 256) {
            int result = countSubstrings(input);
            printf("Count of substrings: %d\n", result);
        } else {
            printf("Input too long.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
    return 0;
}