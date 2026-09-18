#include <stdio.h>
#include <string.h>

int find_last_occurrence(char* str, char ch) {
    int lastIndex = -1;
    int i;
    
    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] == ch)
            lastIndex = i;
    }
    return lastIndex;
}

int main() {
    char str[100];
    char ch;
    int index;
    
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = '\0'; 

    printf("Enter character to find last occurrence: ");
    scanf(" %c", &ch);
    
    index = find_last_occurrence(str, ch);

    if(index == -1) {
        printf("Character not found in the string.\n");
    } else {
        printf("Last occurrence of '%c' is at index %d.\n", ch, index);
    }
    
    return 0;
}