#include <stdio.h>

void replaceSpaces(char *str, const char ch) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = ch;
        }
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[101] = "";
    char ch = '\0';
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    printf("Enter the character to replace spaces with: ");
    scanf("%c", &ch);
    replaceSpaces(str, ch);
    printf("Modified string: %s", str);
    return 0;
}