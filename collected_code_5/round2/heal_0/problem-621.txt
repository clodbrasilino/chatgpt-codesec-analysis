#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void incrementString(char* str, int k) {
    for(int i=0; i<strlen(str); i++) {
        if(isdigit(str[i])) {
            int num = str[i] - '0';
            num = (num + k) % 10;
            str[i] = num + '0';
        }
    }
}

int main() {
    char str[100];
    int k;
  
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
  
    printf("Enter a value to increment: ");
    scanf("%d", &k);
  
    incrementString(str, k);
  
    printf("Result: %s\n", str);
  
    return 0;
}