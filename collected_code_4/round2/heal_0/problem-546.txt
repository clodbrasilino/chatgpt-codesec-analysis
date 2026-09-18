#include <stdio.h>
#include <string.h>

char* find_last_occurrence(const char* str, char ch) {
    char* ptr = strrchr(str, ch);
    return ptr;
}

int main() {
    char str[100];
    char ch;

    printf("\nEnter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';  

    printf("\nEnter the character to find: ");
    scanf(" %c", &ch);

    char* idx = find_last_occurrence(str, ch);

    if(idx == NULL) {
        printf("\nThe character was not found.\n");
    } else {
        printf("\nThe character was found at index: %ld.\n", idx - str);
    }

    return 0;
}