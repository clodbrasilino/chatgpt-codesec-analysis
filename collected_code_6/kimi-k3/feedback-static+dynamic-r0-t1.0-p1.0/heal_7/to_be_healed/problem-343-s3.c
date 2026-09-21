#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    *digit_count = 0;
    *letter_count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            (*digit_count)++;
        } else if (isalpha((unsigned char)str[i])) {
            (*letter_count)++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024];
    int digit_count, letter_count;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strcspn(str, "\n");
        if (str[len] == '\n') {
            str[len] = '\0';
        } else if (len == sizeof(str) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }

        count_digits_and_letters(str, &digit_count, &letter_count);
        printf("Number of digits: %d\n", digit_count);
        printf("Number of letters: %d\n", letter_count);
    }
    return 0;
}