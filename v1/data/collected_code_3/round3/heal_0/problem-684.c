#include <stdio.h>
#include <string.h>

int countOccurrences(char *str, char c) {
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return count;
}

int main() {
    char str[] = "Hello, World!";
    char c = 'l';
    printf("Number of occurrences of %c: %d\n", c, countOccurrences(str, c));
    return 0;
}