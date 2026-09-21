#include <stdio.h>
#include <ctype.h>

void count_characters(const char *str, int *alphabets, int *digits, int *specials) {
    if (str == NULL || alphabets == NULL || digits == NULL || specials == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else if (!isspace((unsigned char)str[i])) {
            (*specials)++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_string[256];
    int alphabets = 0;
    int digits = 0;
    int specials = 0;

    if (fgets(input_string, sizeof(input_string), stdin) != NULL) {
        count_characters(input_string, &alphabets, &digits, &specials);
        
        printf("Alphabets: %d\n", alphabets);
        printf("Digits: %d\n", digits);
        printf("Special Characters: %d\n", specials);
    }

    return 0;
}