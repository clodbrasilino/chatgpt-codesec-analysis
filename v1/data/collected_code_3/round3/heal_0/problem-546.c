#include <stdio.h>
#include <string.h>

int find_last_occurrence(char* str, char ch) {
    int index = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            index = i;
        }
    }
    return index;
}

int main() {
    char str[100];
    char ch;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    printf("Enter a character: ");
    scanf("%c", &ch);
    int index = find_last_occurrence(str, ch);
    if (index == -1) {
        printf("Character not found in the string.\n");
    } else {
        printf("Last occurrence of '%c' is at index %d.\n", ch, index);
    }
    return 0;
}