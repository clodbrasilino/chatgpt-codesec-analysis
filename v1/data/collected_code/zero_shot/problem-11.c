#include <stdio.h>
#include <string.h>

void removeOccurrences(char* str, char c) {
    int len = strlen(str);
    int i, j;
    int first = -1; // index of first occurrence of c
    int last = -1; // index of last occurrence of c

    // Find index of first and last occurrence of c in str
    for (i = 0; i < len; i++) {
        if (str[i] == c) {
            if (first == -1) {
                first = i;
            }
            last = i;
        }
    }

    // No occurrence of c found in str
    if (first == -1) {
        return;
    }

    // Shift characters to overwrite first and last occurrence of c
    for (j = first; j < len - 1; j++) {
        str[j] = str[j + 1];
    }

    // Set new length of the string
    len--;

    // Shift characters to overwrite last occurrence of c
    for (j = last; j < len - 1; j++) {
        str[j] = str[j + 1];
    }

    // Terminate the string
    str[len - 1] = '\0';
}

int main() {
    char str[100];
    char c;

    // Read the string and character from the user
    printf("Enter a string: ");
    scanf("%s", str);
    printf("Enter a character: ");
    scanf(" %c", &c);

    // Remove first and last occurrence of c from the string
    removeOccurrences(str, c);

    // Print the modified string
    printf("Modified string: %s\n", str);

    return 0;
}