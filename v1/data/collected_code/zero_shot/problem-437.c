#include<stdio.h>

void removeOddCharacters(char *str) {
    int i, j;
  
    // Traverse the string
    for (i = 0; str[i] != '\0'; i++) {
        // Check if character at current index is odd
        if (i % 2 == 0) {
            // If odd, copy it to the next even index
            str[j++] = str[i];
        }
    }
  
    // Add null character at the end of new string
    str[j] = '\0';
}

int main() {
    char str[100];
  
    // Input the string
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
  
    // Remove odd characters from the string
    removeOddCharacters(str);
  
    // Output the modified string
    printf("Modified string: %s", str);
  
    return 0;
}