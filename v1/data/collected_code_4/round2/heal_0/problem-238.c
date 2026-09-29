#include <stdio.h>
#include <string.h>

int countSubstrings(char* s) {
    int length = strlen(s);
    return length * (length + 1) / 2;
}

int main() {
    char s[100];
    printf("Enter a string: ");
    scanf("%s", s);

    int result = countSubstrings(s);
    printf("Number of non-empty substrings is: %d\n", result);

    return 0;
}