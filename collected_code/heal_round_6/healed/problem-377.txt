#include<stdio.h>
#include<string.h>

#define MAX_SIZE 100

void removeChar(char* str, char c) {
    if(str == NULL)
        return;

    int count = 0;
    for (int i = 0; str[i]; i++) {
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
    if(fgets(str, MAX_SIZE, stdin)) {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
    }

    printf("Enter the character to remove: ");
    if(scanf("%c", &c)) {
        removeChar(str, c);
    }
  
    printf("String after removing character '%c': %s\n", c, str);

    return 0;
}