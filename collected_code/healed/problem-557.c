#include <stdio.h>

void toggleCase(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

int main() {
    char str[] = "Hello, World!";
  
    printf("Before toggling: %s\n", str);
  
    toggleCase(str);
  
    printf("After toggling: %s\n", str);
  
    return 0;
}