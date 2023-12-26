#include <stdio.h>

int countOccurrence(const char str[], char ch) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            count++;
        }
    }
    return count;
}

int main() {
    const char str[] = "Hello, World!";
    char ch = 'l';
    int occurrence = countOccurrence(str, ch);
    printf("Occurrence of %c in string: %d", ch, occurrence);

    return 0;
}