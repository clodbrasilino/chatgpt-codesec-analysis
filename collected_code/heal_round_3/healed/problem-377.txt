#include<stdio.h>
#include<string.h>

#define MAX_SIZE 100

void removeChar(char* str, char c) {
    int count = 0;
    int i;
    size_t length = strlen(str);
    for (i = 0; i < length; i++) {
        if (str[i] != c) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

int main() {
    char str[MAX_SIZE];
    char c; 

    printf("Enter a string: ");
    fgets(str, MAX_SIZE, stdin);
    str[strcspn(str, "\n")] = 0;

    printf("Enter the character to remove: ");
    scanf(" %c", &c);
    if (c != '\n') {
        removeChar(str, c);
    }

    printf("String after removing character '%c': %s\n", c, str);

    return 0;
}