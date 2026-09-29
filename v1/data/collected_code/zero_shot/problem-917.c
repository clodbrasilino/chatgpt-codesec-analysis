#include <stdio.h>

void findSequences(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            putchar(str[i]);
            i++;
            while (str[i] >= 'a' && str[i] <= 'z') {
                putchar(str[i]);
                i++;
            }
            putchar('\n');
        }
        else {
            i++;
        }
    }
}

int main() {
    char str[] = "ABcD efGhIjKlM";
    findSequences(str);
    return 0;
}