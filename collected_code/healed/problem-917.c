#include <stdio.h>

void findSequences(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            putchar(str[i]);
            i++;
            while (str[i] != '\0' && str[i] >= 'a' && str[i] <= 'z') {
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
    const char str[] = "ABcD efGhIjKlM";
    findSequences(str);
    return 0;
}