#include <stdio.h>
#include <ctype.h>

void count_chars(const char *str, int *letters, int *digits) {
    /* Possible weaknesses found:
     *  Either the condition 'letters==NULL' is redundant or there is possible null pointer dereference: letters. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    *letters = 0;
    /* Possible weaknesses found:
     *  Either the condition 'digits==NULL' is redundant or there is possible null pointer dereference: digits. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    *digits = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'digits==NULL' is not redundant
     *  Assuming that condition 'letters==NULL' is not redundant
     */
    if (str == NULL || letters == NULL || digits == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            (*letters)++;
        } else if (isdigit((unsigned char)str[i])) {
            (*digits)++;
        }
    }
}

int main(void) {
    const char *text = "Hello World 12345!";
    int letters = 0;
    int digits = 0;
    
    count_chars(text, &letters, &digits);
    
    printf("Letters: %d\n", letters);
    printf("Digits: %d\n", digits);
    
    return 0;
}