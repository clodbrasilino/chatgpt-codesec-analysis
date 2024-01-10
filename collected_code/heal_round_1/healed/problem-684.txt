#include <stdio.h>

int countOccurrences(const char *str, char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "ababab";
    char c = 'a';

    int occurrences = countOccurrences(str, c);
    printf("Number of occurrences of '%c' in the string: %d\n", c, occurrences);

    return 0;
}