#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increment_string_num(char *str, size_t len, int k) {
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            str[i] = (str[i] - '0' + k) % 10 + '0';
        }
    }
    return 0;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[1024];
    int k;

    printf("Enter a string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    str1[strcspn(str1, "\n")] = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str1);

    printf("Enter an integer k: ");
    if (scanf("%d", &k) != 1) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((getchar()) != '\n'); // Clear the input buffer

    increment_string_num(str1, len, k);

    printf("Updated string: %s\n", str1);
    return EXIT_SUCCESS;
}