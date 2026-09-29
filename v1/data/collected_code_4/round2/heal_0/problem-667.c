#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_vowels(char *str) {
    int count = 0;
    int length = strlen(str);

    for(int i = 0; i < length; i++) {
        char c = tolower(str[i]);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, 100, stdin);

    int vowels_count = count_vowels(str);
    printf("Number of vowels in the string is: %d\n", vowels_count);

    return 0;
}