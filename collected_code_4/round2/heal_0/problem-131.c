#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

char* reverseVowels(char* s) {
    int i = 0, j = strlen(s) - 1;
    char *result = (char *)malloc((strlen(s) + 1) * sizeof(char));
    strcpy(result, s);

    while (i < j) {
        if (!isVowel(s[i])) {
            i++;
            continue;
        }
        if (!isVowel(s[j])) {
            j--;
            continue;
        }
        result[i] = s[j];
        result[j] = s[i];
        i++;
        j--;
    }
    return result;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%99[^\n]", str);
    char* reversed = reverseVowels(str);
    printf("String after reversing vowels: %s\n", reversed);
    free(reversed);
    return 0;
}