#include <stdio.h>
#include <ctype.h>

int countLowercase(const char *str) {
    int count = 0;
    while (*str) {
        if (islower((unsigned char)*str)) {
            count++;
        }
        str++;
    }
    return count;
}

int main() {
    const char *testString = "Hello, World!";
    int lowercaseCount = countLowercase(testString);
    printf("Number of lowercase letters: %d\n", lowercaseCount);
    return 0;
}