#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_digits(const char *str, size_t len) {
    int digits = 0;
    size_t i;
    for (i = 0; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            digits++;
        }
    }
    return digits;
}

int count_letters(const char *str, size_t len) {
    int letters = 0;
    size_t i;
    for (i = 0; i < len; i++) {
        if (isalpha((unsigned char)str[i])) {
            letters++;
        }
    }
    return letters;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    size_t len;
    size_t max_len = sizeof(input) - 1;
    
    printf("Enter a string: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    input[max_len] = '\0';
    len = strnlen(input, max_len);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    } else if (len == max_len && input[max_len] == '\0') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    if (len == 0) {
        printf("Empty input.\n");
        return 0;
    }
    
    int digits = count_digits(input, len);
    int letters = count_letters(input, len);
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);
    
    return 0;
}