#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 256
#define MAX_INPUT_LENGTH (INPUT_BUFFER_SIZE - 1)

void count_digits_and_letters(const char *str, int *digit_count, int *letter_count) {
    *digit_count = 0;
    *letter_count = 0;

    if (str == NULL) {
        return;
    }

    for (size_t i = 0; i < MAX_INPUT_LENGTH && str[i] != '\0'; i++) {
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
    char input[INPUT_BUFFER_SIZE] = {0};
    int digits = 0;
    int letters = 0;
    size_t input_length;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[input_length - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'input_length' is assigned a value that is never used. [unreadVariable]
         */
        input_length--;
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    count_digits_and_letters(input, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}