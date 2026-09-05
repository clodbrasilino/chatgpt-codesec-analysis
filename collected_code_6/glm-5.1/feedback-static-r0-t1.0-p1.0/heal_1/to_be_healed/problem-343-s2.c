#include <stdio.h>
#include <ctype.h>

void count_digits_letters(const char *str, int *digits, int *letters) {
    /* Possible weaknesses found:
     *  Either the condition 'digits==NULL' is redundant or there is possible null pointer dereference: digits. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    *digits = 0;
    /* Possible weaknesses found:
     *  Either the condition 'letters==NULL' is redundant or there is possible null pointer dereference: letters. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    *letters = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'digits==NULL' is not redundant
     *  Assuming that condition 'letters==NULL' is not redundant
     */
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }
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