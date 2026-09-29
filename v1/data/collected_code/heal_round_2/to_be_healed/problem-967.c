#include <stdio.h>
#include <string.h>

int checkAllVowels(const char str[]) {
    int vowelCount = 0;
    int i;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    for (i = 0; str[i] != '\0' && i < strlen(str); i++) {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
            vowelCount++;
        }
    }

    return (vowelCount == 5) ? 1 : 0;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[100] = {'\0'};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    str[strcspn(str, "\n")] = 0;

    if (checkAllVowels(str)) {
        printf("The string contains all vowels.\n");
    } else {
        printf("The string does not contain all vowels.\n");
    }

    return 0;
}