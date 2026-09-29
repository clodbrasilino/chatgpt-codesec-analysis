#include <stdio.h>
#include <ctype.h>

void countDigitsAndLetters(const char *str, int *digits, int *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else if (isalpha((unsigned char)*str)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    const char *testString = "Hello World! 123";
    int digitsCount = 0;
    int lettersCount = 0;

    countDigitsAndLetters(testString, &digitsCount, &lettersCount);

    printf("String: %s\n", testString);
    printf("Digits: %d\n", digitsCount);
    printf("Letters: %d\n", lettersCount);

    return 0;
}