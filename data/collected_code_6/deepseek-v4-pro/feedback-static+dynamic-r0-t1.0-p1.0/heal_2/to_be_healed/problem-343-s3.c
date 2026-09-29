#include <stdio.h>
#include <ctype.h>

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    *digit_count = 0;
    *letter_count = 0;

    if (str == NULL) {
        return;
    }

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
    char input[256];
    int digits = 0;
    int letters = 0;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        if (input[len] == '\n') {
            input[len] = '\0';
            break;
        }
        len++;
    }

    if (len == sizeof(input)) {
        input[sizeof(input) - 1] = '\0';
    }

    count_digits_and_letters(input, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}