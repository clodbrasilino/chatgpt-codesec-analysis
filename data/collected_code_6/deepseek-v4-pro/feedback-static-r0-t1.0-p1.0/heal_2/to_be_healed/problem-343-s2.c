#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_digits(const char *str, size_t len) {
    int digits = 0;
    size_t i;
    for (i = 0; i < len && str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            digits++;
        }
    }
    return digits;
}

int count_letters(const char *str, size_t len) {
    int letters = 0;
    size_t i;
    for (i = 0; i < len && str[i] != '\0'; i++) {
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
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len >= sizeof(input)) {
        printf("Input too long.\n");
        return 1;
    }
    
    int digits = count_digits(input, sizeof(input));
    int letters = count_letters(input, sizeof(input));
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);
    
    return 0;
}