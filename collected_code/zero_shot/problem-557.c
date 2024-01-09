#include <stdio.h>

void toggleCase(char str[]) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // Convert lowercase to uppercase
        }
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // Convert uppercase to lowercase
        }
        i++;
    }
}

int main() {
    char str[] = "Hello, World!";
  
    printf("Before toggling: %s\n", str);
  
    toggleCase(str);
  
    printf("After toggling: %s\n", str);
  
    return 0;
}