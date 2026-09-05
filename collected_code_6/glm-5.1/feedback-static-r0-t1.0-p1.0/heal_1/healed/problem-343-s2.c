#include <stdio.h>
#include <ctype.h>

void count_digits_letters(const char *str, int *digits, int *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }
    *digits = 0;
    *letters = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        } else if (isalpha((unsigned char)str[i])) {
            (*letters)++;
        }
    }
}

int main(void) {
    const char *text = "Hello World 12345!";
    int d, l;
    count_digits_letters(text, &d, &l);
    printf("Digits: %d\nLetters: %d\n", d, l);
    return 0;
}