#include <stdio.h>
#include <string.h>

char* find_last_occurrence(char* str, char ch) {
    char* ptr = strrchr(str, ch);
    return ptr;
}

int main() {
    char str[100];
    char ch;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    printf("Enter a character: ");
    scanf("%c", &ch);
    char* ptr = find_last_occurrence(str, ch);
    if (ptr != NULL)
        printf("Last occurrence of '%c' in '%s' is at position: %ld\n", ch, str, ptr-str+1);
    else
        printf("Character not found\n");
    return 0;
}