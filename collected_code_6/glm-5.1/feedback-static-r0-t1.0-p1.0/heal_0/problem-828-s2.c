#include <stdio.h>
#include <ctype.h>

void count_chars(const char *str, int *alphabets, int *digits, int *specials) {
    if (str == NULL || alphabets == NULL || digits == NULL || specials == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    size_t i = 0;
    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            (*alphabets)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else {
            (*specials)++;
        }
        i++;
    }
}

int main(void) {
    const char *input = "Hello World! 123 @#$";
    int alpha = 0;
    int digit = 0;
    int special = 0;

    count_chars(input, &alpha, &digit, &special);

    printf("Alphabets: %d\n", alpha);
    printf("Digits: %d\n", digit);
    printf("Special characters: %d\n", special);

    return 0;
}