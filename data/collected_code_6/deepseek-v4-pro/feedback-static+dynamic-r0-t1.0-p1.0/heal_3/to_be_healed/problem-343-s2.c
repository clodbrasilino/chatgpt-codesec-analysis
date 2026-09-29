#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

int count_digits(const char *str, size_t max_len) {
    int digits = 0;
    size_t i;
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            digits++;
        }
    }
    return digits;
}

int count_letters(const char *str, size_t max_len) {
    int letters = 0;
    size_t i;
    for (i = 0; i < max_len && str[i] != '\0'; i++) {
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
    char input[BUFFER_SIZE];
    size_t input_len;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len >= sizeof(input)) {
        printf("Input too long.\n");
        return 1;
    }
    
    int digits = count_digits(input, input_len);
    int letters = count_letters(input, input_len);
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);
    
    return 0;
}